 #include "DrawableObject.h"

#include "Transformation/CompositeTransformation.h"
#include "Transformation/Rotation.h"
#include "Transformation/Scale.h"
#include "Transformation/Translation.h"

// Include GLM
#include <glm/gtc/constants.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

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

	if (parametricLine_)
		parametricLine_->update(deltaTime);
	if (cubicLine_)
		cubicLine_->update(deltaTime);
	if (cubicSpline_)
		cubicSpline_->update(deltaTime);
}

glm::mat4 DrawableObject::getModelMatrix()
{
	glm::mat4 modelMatrix = transformation_->getModelMatrix();

	if (parametricLine_) {
		modelMatrix[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); //we dump the old pos to move on the line
		return parametricLine_->getModelMatrix() * modelMatrix;
	}
	if (cubicLine_) {
		modelMatrix[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); //we dump the old pos to move on the line
		return cubicLine_->getModelMatrix() * modelMatrix;
	}
	if (cubicSpline_) {
		modelMatrix[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); //we dump the old pos to move on the line
		return cubicSpline_->getModelMatrix() * modelMatrix;
	}

	return modelMatrix;
}

void DrawableObject::setParametricLine(glm::vec3 start, glm::vec3 end, float speed)
{
	parametricLine_ = std::make_unique<ParametricLine>(start, end, speed);
}

CubicLine* DrawableObject::setCubicLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float speed) {
	cubicLine_ = std::make_unique<CubicLine>(p1, p2, p3, p4, speed);
	return cubicLine_.get();
}

void DrawableObject::draw()
{
	material_.bind();

	ShaderProgram* shaderProgram = material_.getShaderProgram();
	if (!shaderProgram) return;

	shaderProgram->updateCameraUniforms();
	shaderProgram->setUniform("modelMatrix", getModelMatrix());
	model_.draw();
}

void DrawableObject::setPosition(glm::vec3 pos) {
	position_ = pos;
}

void DrawableObject::setCubicSpline(std::vector<glm::vec3> points, float speed)
{
	cubicSpline_ = std::make_unique<CubicSpline>(std::move(points), speed);
}
