#pragma once

#include "Scene.h"

#include <cstddef>
#include <vector>
#include <memory>

struct GLFWwindow;

//Michal Poncza
class Application
{
public:
	Application() = default;
	void initialization();
	void createScenes();
	void run();

	void onWindowResize(int width, int height);
	void onCursorPos(double x, double y);

private:
	static void keyCallback(GLFWwindow* window, int key, int scancodes, int action, int mods);
	void switchScene(size_t index);

	GLFWwindow* window_ = nullptr;
	std::vector<std::unique_ptr<Scene>> scenes_;
	size_t activeScene_ = 0;

	double lastX_ = 400.0;
	double lastY_ = 300.0;
	float aspect_ = 4.0f / 3.0f;
};
