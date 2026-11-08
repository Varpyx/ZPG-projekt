#include "CompositeTransformation.h"

void CompositeTransformation::addTransformation(std::unique_ptr<Transformation> transformation)
{
	transformations_.push_back(std::move(transformation));
}

glm::mat4 CompositeTransformation::getModelMatrix()
{
	glm::mat4 modelMatrix(1.0f);
	for (auto& transformation : transformations_)
	{
		modelMatrix = modelMatrix * transformation->getModelMatrix();
	}
	return modelMatrix;
}

void CompositeTransformation::update(float deltaTime)
{
	for (auto& transformation : transformations_)
	{
		transformation->update(deltaTime);
	}
}
