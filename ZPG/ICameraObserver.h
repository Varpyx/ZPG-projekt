#pragma once
#include <glm/glm.hpp>

class ICameraObserver
{
public:
	virtual ~ICameraObserver() = default;
	virtual void onCameraChanged(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) = 0;
};