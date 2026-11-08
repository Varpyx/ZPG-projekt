#include "Translation.h"

#include <glm/gtc/matrix_transform.hpp>

Translation::Translation(glm::vec3 offset, glm::vec3 velocity)
	: offset_(offset), velocity_(velocity)
{
}

glm::mat4 Translation::getModelMatrix()
{
	return glm::translate(glm::mat4(1.0f), offset_);
}

void Translation::update(float deltaTime)
{
	offset_ += velocity_ * deltaTime;
}

void Translation::setOffset(glm::vec3 offset)
{
	offset_ = offset;
}

void Translation::setVelocity(glm::vec3 velocity)
{
	velocity_ = velocity;
}

glm::vec3 Translation::getOffset()
{
	return offset_;
}

glm::vec3 Translation::getVelocity()
{
	return velocity_;
}
