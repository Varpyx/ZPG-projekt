#include "DrawableObject.h"

// Include GLM
#include <glm/gtc/constants.hpp>

DrawableObject::DrawableObject(Model model, ShaderProgram* shaderProgram,
	const glm::vec3& color, float scale, const glm::vec3& offset)
	: model_(model), shaderProgram_(shaderProgram), color_(color)
{
	transformation_.setScale(scale);
	transformation_.setOffset(offset);
}

void DrawableObject::update(float deltaTime)
{
	transformation_.rotateY(deltaTime * glm::radians(45.0f));
}

void DrawableObject::draw2()
{
	if (!shaderProgram_ || !shaderProgram_->use())
		return;

	shaderProgram_->setUniform("scale", transformation_.getScale());
	shaderProgram_->setUniform("offset", transformation_.getOffset());
	shaderProgram_->setUniform("angleY", transformation_.getAngleY());
	shaderProgram_->setUniform("anglePlaneXY", transformation_.getAnglePlaneXY());
	shaderProgram_->setUniform("fragmentColor", color_);

	model_.draw();
}

void DrawableObject::draw()
{
	if (!shaderProgram_ || !shaderProgram_->use())
		return;

	shaderProgram_->setUniform("modelMatrix", transformation_.getModelMatrix());
	shaderProgram_->setUniform("fragmentColor", color_);

	model_.draw();
}