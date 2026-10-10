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

void DrawableObject::draw()
{
	if (!shaderProgram_ || !shaderProgram_->use())
		return;

	shaderProgram_->setUniform("modelMatrix", transformation_.getModelMatrix());
	shaderProgram_->setUniform("fragmentColor", color_);

	model_.draw();
}