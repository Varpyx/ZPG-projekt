#pragma once

// Include GLM
#include <glm/glm.hpp>

#include "Transformation.h"

class Translation : public Transformation
{
public:
	Translation(glm::vec3 offset = glm::vec3(0.0f), glm::vec3 velocity = glm::vec3(0.0f));

	glm::mat4 getModelMatrix() override;
	void update(float deltaTime) override;

	void setOffset(glm::vec3 offset);
	void setVelocity(glm::vec3 velocity);
	glm::vec3 getOffset();
	glm::vec3 getVelocity();

private:
	glm::vec3 offset_ = glm::vec3(0.0f);
	glm::vec3 velocity_ = glm::vec3(0.0f);
};
