// Include GLAD
// Implementace GLADu je mimo include guard, takze se musi undefinovat,
// jinak se vygeneruje znovu pri kazdem dalsim include v hlavickach.
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

// Include GLFW
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Models/suzi_smooth.h"
#include "Models/sphere.h"
#include "Models/bushes.h"
#include "Models/login.h"
#include <stdlib.h>
#include <stdio.h>

static void error_callback(int error, const char* description) { fputs(description, stderr); }

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

void Application::keyCallback(GLFWwindow* window, int key, int scancodes, int action, int mods)
{
	Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (!application)
		return;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	// Cislovnice 1..9 prepinaji sceny
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
			application->switchScene(static_cast<size_t>(key - GLFW_KEY_1));
	}
}

void Application::switchScene(size_t index)
{
	if (index >= scenes_.size())
	{
		printf("Scena %zu neexistuje\n", index + 1);
		return;
	}

	activeScene_ = index;
	printf("Scena %zu\n", activeScene_ + 1);
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

	// Callback se dostane k instanci Application pres user pointer
	glfwSetWindowUserPointer(window_, this);
	glfwSetKeyCallback(window_, Application::keyCallback);

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

void Application::createScenes()
{
	// reserve, aby se nepremistily programy, na ktere ukazuji DrawableObjecty
	scenes_.reserve(4);

	// Scena 1: suzi
	Scene* scene1 = &scenes_.emplace_back();
	ShaderProgram* shader1 = scene1->addShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	scene1->addDrawableObject(
		Model(suziSmooth, sizeof(suziSmooth) / (6 * sizeof(float))), shader1,
		glm::vec3(1.0f, 0.7f, 0.2f), 0.4f);

	// Scena 2: koule
	Scene* scene2 = &scenes_.emplace_back();
	ShaderProgram* shader2 = scene2->addShaderProgram("shaders/basic2.vert", "shaders/basic2.frag");
	scene2->addDrawableObject(
		Model(sphere, 2880), shader2,
		glm::vec3(0.4f, 0.6f, 1.0f), 0.4f);

	// Scena 3: kere
	Scene* scene3 = &scenes_.emplace_back();
	ShaderProgram* shader3 = scene3->addShaderProgram("shaders/basic3.vert", "shaders/basic3.frag");

	float offsetX = -0.9f;
	for(int i = 0; i < 20; i++)
	{
		scene3->addDrawableObject(Model(bushes, 8730), shader3,	glm::vec3(0.6f, 1.0f, 0.5f), 0.4f, glm::vec3(offsetX, 0.1f, 0.1f));
		offsetX += 0.1f;
	}

	//Scena 4: login
	Scene* scene4 = &scenes_.emplace_back();
	ShaderProgram* shader4 = scene4->addShaderProgram("shaders/login.vert", "shaders/login.frag");
	scene4->addDrawableObject(
		Model(login, sizeof(login) / (6 * sizeof(float))), shader4,
		glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	printf("Vytvoreno %zu scen, prepinej klavesami 1-%zu\n", scenes_.size(), scenes_.size());
}

void Application::run()
{
	if (scenes_.empty())
		return;

	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window_))
	{
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;

		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Scene& scene = scenes_[activeScene_];
		scene.update(deltaTime);
		scene.draw();

		// Display the rendered frame and process events
		glfwSwapBuffers(window_);
		glfwPollEvents();
	}

	// Clean up and terminate GLFW
	glfwDestroyWindow(window_);
	glfwTerminate();
}