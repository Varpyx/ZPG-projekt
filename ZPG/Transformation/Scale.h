#pragma once

// Include GLM
#include <glm/glm.hpp>

#include "Transformation.h"

class Scale : public Transformation
{
public:
	Scale(float scale = 1.0f);

	glm::mat4 getModelMatrix() override;

	void setScale(float scale);
	float getScale();

private:
	float scale_ = 1.0f;
};
