// Include GLAD
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

// Include GLFW
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Models/suzi_smooth.h"
#include "Models/sphere.h"
#include "Models/bushes.h"
#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		printf("space \n");
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void Application::initialization()
{
	// Initialize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	window_ = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window_)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window_);
	glfwSwapInterval(1);

	// Initialize GLAD and load OpenGL function pointers
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		printf("GLAD initialization failed\n");
		exit(EXIT_FAILURE);
	}

	// Get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	// Set GLFW callback functions
	glfwSetErrorCallback(error_callback);

	glfwSetKeyCallback(window_, key_callback);

	glfwSetCursorPosCallback(window_, cursor_callback);

	glfwSetMouseButtonCallback(window_, button_callback);

	glfwSetWindowFocusCallback(window_, window_focus_callback);

	glfwSetWindowIconifyCallback(window_, window_iconify_callback);

	glfwSetWindowSizeCallback(window_, window_size_callback);

	// Get framebuffer size and set the viewport
	int width, height;
	glfwGetFramebufferSize(window_, &width, &height);
	glViewport(0, 0, width, height);

	//Do depth comparisons and update the depth buffer.
	glEnable(GL_DEPTH_TEST);
}

void Application::createScene()
{
	// Create and link the shader programs
	shader_  = Shader("shaders/basic.vert",  "shaders/basic.frag");
	shader2_ = Shader("shaders/basic2.vert", "shaders/basic2.frag");
	shader3_ = Shader("shaders/basic3.vert", "shaders/basic3.frag");


	// 6 floats per vertex, so the count is the array size divided by 6
	objects_.push_back(DrawableObject(Model(suziSmooth, sizeof(suziSmooth) / (6 * sizeof(float))), shader_));
	objects_.push_back(DrawableObject(Model(sphere, 2880), shader2_));
	objects_.push_back(DrawableObject(Model(bushes, 8730), shader3_));
}

void Application::run()
{
	while (!glfwWindowShouldClose(window_))
	{
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (const DrawableObject& object : objects_)
			object.draw();

		// Display the rendered frame and process events
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}

	// Clean up and terminate GLFW
	glfwDestroyWindow(window_);
	glfwTerminate();
}
