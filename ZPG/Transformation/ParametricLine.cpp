#include "ParametricLine.h"

#include <glm/gtc/matrix_transform.hpp>

ParametricLine::ParametricLine(glm::vec3 start, glm::vec3 end, float speed)
	: start_(start), end_(end), speed_(speed)
{
}

glm::mat4 ParametricLine::getModelMatrix()
{
	glm::vec3 position = start_ + (end_ - start_) * t_; //Parametric equation of a line
	return glm::translate(glm::mat4(1.0f), position);
}

void ParametricLine::update(float deltaTime)
{
	t_ += direction * speed_ * deltaTime;
	
	if (t_ >= 1.0f) {
		t_ = 1.0f;
		direction = -1;
	}
	else if (t_ <= 0.0f) {
		t_ = 0.0f;
		direction = 1;
	}
}