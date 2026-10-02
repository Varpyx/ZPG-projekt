#pragma once

#include "Scene.h"

#include <cstddef>
#include <vector>

struct GLFWwindow;

class Application
{
public:
	Application() = default;
	void initialization();
	void createScenes();
	void run();

private:
	static void keyCallback(GLFWwindow* window, int key, int scancodes, int action, int mods);
	void switchScene(size_t index);

	GLFWwindow* window_ = nullptr;
	std::vector<Scene> scenes_;
	size_t activeScene_ = 0;
};