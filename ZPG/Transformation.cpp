#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>
void Transformation::translate(const glm::vec3& delta)
{
	offset_ += delta;
}

void Transformation::rotateY(float alpha)
{
	angleY_ += alpha;
}

void Transformation::rotatePlaneXY(float alpha)
{
	anglePlaneXY_ += alpha;
}

void Transformation::setScale(float scale)
{
	scale_ = scale;
	if (scale_ < 0.01f) scale_ = 0.01f;
}

void Transformation::reset()
{
	offset_ = glm::vec3(0.0f);
	angleY_ = 0.0f;
	anglePlaneXY_ = 0.0f;
	scale_ = 1.0f;
}

glm::mat4 Transformation::getModelMatrix()
{
	glm::mat4 M = glm::mat4(1.0f);
	M = glm::translate(M, offset_);
	M = glm::rotate(M, glm::radians(anglePlaneXY_), glm::vec3(0.0f, 0.0f, 1.0f));
	M = glm::rotate(M, glm::radians(angleY_), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(scale_));
	return M;
}