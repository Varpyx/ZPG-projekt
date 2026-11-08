#pragma once

#include <memory>
#include <vector>

#include "Transformation.h"

class CompositeTransformation : public Transformation
{
public:
	void addTransformation(std::unique_ptr<Transformation> transformation);
	glm::mat4 getModelMatrix() override;
	void update(float deltaTime) override;

private:
	std::vector<std::unique_ptr<Transformation>> transformations_;
};
