#pragma once

#include "Scene.h"

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
	Scene scene_;
};