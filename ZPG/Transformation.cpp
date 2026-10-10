#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Translation::getModelMatrix()
{
	return glm::translate(glm::mat4(1.0f), offset_);
}

glm::mat4 Rotation::getModelMatrix()
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(angle_), axis_);
}

glm::mat4 Scale::getModelMatrix()
{
	return glm::scale(glm::mat4(1.0f), glm::vec3(scale_));
}

void CompositeTransformation::addTransformation(std::unique_ptr<Transformation> transformation)
{
	transformations_.push_back(std::move(transformation));
}

glm::mat4 CompositeTransformation::getModelMatrix()
{
	glm::mat4 modelMatrix(1.0f);
	for (const auto& transformation : transformations_)
	{
		modelMatrix = modelMatrix * transformation->getModelMatrix();
	}
	return modelMatrix;
}

void CompositeTransformation::update(float deltaTime)
{
	for (const auto& transformation : transformations_)
	{
		transformation->update(deltaTime);
	}
}