#pragma once

// Include GLM
#include <glm/glm.hpp>

//Michal Poncza
class Transformation
{
public:
	virtual ~Transformation() = default;
	virtual glm::mat4 getModelMatrix() = 0;
	virtual void update(float deltaTime) {}
};
