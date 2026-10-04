#include "Transformation.h"

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