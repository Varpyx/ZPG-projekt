#pragma once

#include "glm/glm.hpp"

#include "Transformation.h"

class ParametricLine : public Transformation
{
public:
	ParametricLine(glm::vec3 start, glm::vec3 end, float speed = 0.2f);

	glm::mat4 getModelMatrix() override;
	void update(float deltaTime) override;

private:
	glm::vec3 start_;
	glm::vec3 end_;
	float speed_;
	float t_ = 0.0f;
	int direction = 1;
	
};