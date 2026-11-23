#pragma once

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Transformation.h"

class CubicLine : public Transformation
{
public:
	CubicLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float speed = 0.2f);

	glm::mat4 getModelMatrix() override;
	void update(float deltaTime) override;

private:
	
	float speed_;
	float t_ = 0.0f;
	int direction = 1;
	glm::mat4 A_;
	glm::mat4x3 B_;
};