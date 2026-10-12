#pragma once
#include <glm/glm.hpp>

class Camera {

private:
	glm::mat4 viewMatrix_;
	glm::mat4 projectionMatrix_;
};