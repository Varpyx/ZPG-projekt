#pragma once
#include <glm/glm.hpp>

//Michal Poncza
class ICameraObserver
{
public:
	virtual ~ICameraObserver() = default;
	virtual void onCameraChanged(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPos) = 0;
};