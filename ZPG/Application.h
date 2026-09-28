#pragma once

#include "DrawableObject.h"

#include <vector>

struct GLFWwindow;

class Application
{
public:
	Application() = default;
	void initialization();
	void createScene();
	void run();

private:
	GLFWwindow* window_ = nullptr;

	Shader shader_, shader2_, shader3_;

	std::vector<DrawableObject> objects_;
};
