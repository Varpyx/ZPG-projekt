#include "Scale.h"

#include <glm/gtc/matrix_transform.hpp>

Scale::Scale(float scale): scale_(scale)
{
}

glm::mat4 Scale::getModelMatrix()
{
	return glm::scale(glm::mat4(1.0f), glm::vec3(scale_));
}

void Scale::setScale(float scale)
{
	scale_ = scale;
}

float Scale::getScale()
{
	return scale_;
}
