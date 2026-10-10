#include "DrawableObject.h"

// Include GLM
#include <glm/gtc/constants.hpp>

DrawableObject::DrawableObject(Model model, ShaderProgram* shaderProgram,
	const glm::vec3& color, float scale, const glm::vec3& offset, float speed, const glm::vec3& velocity)
	: model_(model), shaderProgram_(shaderProgram), color_(color)
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
	if (!shaderProgram_ || !shaderProgram_->use())
		return;

	shaderProgram_->setUniform("modelMatrix", getModelMatrix());
	shaderProgram_->setUniform("fragmentColor", color_);

	model_.draw();
}

