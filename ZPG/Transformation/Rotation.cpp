#include "Rotation.h"

#include <glm/gtc/matrix_transform.hpp>

Rotation::Rotation(glm::vec3 axis, float angle, float speed)
	: axis_(axis), angle_(angle), speed_(speed)
{
}

glm::mat4 Rotation::getModelMatrix()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle_), axis_);
}

void Rotation::update(float deltaTime)
{
	angle_ += speed_ * deltaTime;
}

void Rotation::setAngle(float angle)
{
	angle_ = angle;
}

void Rotation::setSpeed(float speed)
{
	speed_ = speed;
}

float Rotation::getAngle()
{
	return angle_;
}

float Rotation::getSpeed()
{
	return speed_;
}
