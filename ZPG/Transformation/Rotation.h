#pragma once

// Include GLM
#include <glm/glm.hpp>

#include "Transformation.h"

class Rotation : public Transformation
{
public:
	Rotation(glm::vec3 axis, float angle = 0.0f, float speed = 0.0f);

	glm::mat4 getModelMatrix() override;
	void update(float deltaTime) override;

	void setAngle(float angle);
	void setSpeed(float speed);
	float getAngle();
	float getSpeed();

private:
	glm::vec3 axis_ = glm::vec3(0.0f, 1.0f, 0.0f);
	float angle_ = 0.0f;
	float speed_ = 0.0f;
};
