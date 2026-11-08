 #include "DrawableObject.h"

#include "Transformation/CompositeTransformation.h"
#include "Transformation/Rotation.h"
#include "Transformation/Scale.h"
#include "Transformation/Translation.h"

// Include GLM
#include <glm/gtc/constants.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <ctime>

DrawableObject::DrawableObject(Model model, Material material,
	float scale, glm::vec3 offset, float speed, glm::vec3 velocity)
	: model_(model), material_(material)
{
	transformation_ = std::make_unique<CompositeTransformation>();
	//transformation_->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, speed));
	transformation_->addTransformation(std::make_unique<Translation>(offset, velocity));
	transformation_->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, speed));
	transformation_->addTransformation(std::make_unique<Scale>(scale));
}

void DrawableObject::addTransformation(std::unique_ptr<Transformation> transformation)
{
	transformation_->addTransformation(std::move(transformation));
}

void DrawableObject::setTransformation(std::unique_ptr<CompositeTransformation> transformation)
{
	transformation_ = std::move(transformation);
}

void DrawableObject::update(float deltaTime)
{
	transformation_->update(deltaTime);
}

glm::mat4 DrawableObject::getModelMatrix()
{
	return transformation_->getModelMatrix();
}

void DrawableObject::draw()
{
	material_.bind();

	ShaderProgram* shaderProgram = material_.getShaderProgram();
	if (!shaderProgram) return;

	shaderProgram->updateCameraUniforms();

	//getting the time
	std::time_t t = std::time(nullptr);
	std::tm now;
	localtime_s(&now, &t);

	// calc for the smooth effect
	float seconds = static_cast<float>(now.tm_sec);
	float minutes = static_cast<float>(now.tm_min) + (seconds / 60.0f);
	float hours = static_cast<float>(now.tm_hour % 12) + (minutes / 60.0f);

	// calc the angles
	float pi = glm::pi<float>();
	float angleSeconds = seconds * (2.0f * pi / 60.0f);
	float angleMinutes = minutes * (2.0f * pi / 60.0f);
	float angleHours = hours * (2.0f * pi / 12.0f);

	shaderProgram->setUniform("angleSeconds", angleSeconds);
	shaderProgram->setUniform("angleMinutes", angleMinutes);
	shaderProgram->setUniform("angleHours", angleHours);

	shaderProgram->setUniform("modelMatrix", getModelMatrix());
	model_.draw();
}

