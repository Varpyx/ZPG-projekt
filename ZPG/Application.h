#pragma once

#include "DrawableObject.h"

#include <vector>

struct GLFWwindow;

class Application
{
public:
	Application() = default;

	// Creates the window, the OpenGL context and the callbacks.
	void initialization();

	// Compiles the shaders and builds every model in the scene.
	void createScene();

	// Renders until the window is closed.
	void run();

private:
	GLFWwindow* window_ = nullptr;

	Shader shader_, shader2_, shader3_;

	std::vector<DrawableObject> objects_;
};
