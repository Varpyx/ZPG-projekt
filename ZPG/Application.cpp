// Include GLAD
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION

// Include GLFW
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Application.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>

//fuctions from example code
static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n");}

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);

	Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (application) {
		application->onWindowResize(width, height);
	}
}

void Application::onWindowResize(int width, int height)
{
	if (height <= 0) {
		return;
	}

	aspect_ = static_cast<float>(width) / static_cast<float>(height);
	for (auto& scene : scenes_) {
		scene->getCamera().setAspect(aspect_);
	}
}

static void cursor_callback(GLFWwindow* window, double x, double y) { 
	Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (application) {
		application->onCursorPos(x, y);
	}
}
void Application::onCursorPos(double x, double y) {
	if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		float xoffset = static_cast<float>(x - lastX_);
		float yoffset = static_cast<float>(y - lastY_);

		lastX_ = x;
		lastY_ = y;

		Camera& cam = scenes_[activeScene_]->getCamera();
		cam.processMouse(xoffset, yoffset);
	} else {
		lastX_ = x;
		lastY_ = y;
	}
}

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}


static void keyCallback(GLFWwindow* window, int key, int scancodes, int action, int mods)
{
	Application* application = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (!application)
		return;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	// Nums 1-9 for switching scenes
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
		{
			application->switchScene(static_cast<size_t>(key - GLFW_KEY_1));
			return;
		}
	}
}

void Application::switchScene(size_t index)
{
	if (index >= scenes_.size())
	{
		printf("Scene %zu doesnt exist\n", index + 1);
		return;
	}

	activeScene_ = index;
	printf("Scene %zu\n", activeScene_ + 1);
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

	// Callback gets to instance Application bcs of pointer
	glfwSetWindowUserPointer(window_, this);
	glfwSetKeyCallback(window_, keyCallback);

	glfwSetCursorPosCallback(window_, cursor_callback);

	glfwSetMouseButtonCallback(window_, button_callback);

	glfwSetWindowFocusCallback(window_, window_focus_callback);

	glfwSetWindowIconifyCallback(window_, window_iconify_callback);

	glfwSetWindowSizeCallback(window_, window_size_callback);

	// Get framebuffer size and set the viewport
	int width, height;
	glfwGetFramebufferSize(window_, &width, &height);
	glViewport(0, 0, width, height);
	aspect_ = (height > 0) ? static_cast<float>(width) / static_cast<float>(height) : 4.0f / 3.0f;

	//Do depth comparisons and update the depth buffer.
	glEnable(GL_DEPTH_TEST);
}

void Application::createScenes() {
	scenes_ = sceneBuilder_.buildScenes(aspect_);
}

void Application::run()
{
	if (scenes_.empty())
		return;

	double lastTime = glfwGetTime();
	float speed = 2.5f;
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window_))
	{
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;

		Camera& cam = scenes_[activeScene_]->getCamera();
		       
		float d = speed * deltaTime;
		if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) cam.toFront(d);
		if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) cam.toBack(d);
		if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) cam.toLeft(d);
		if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) cam.toRight(d);
		if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS) cam.toUp(d);
		if (glfwGetKey(window_, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) cam.toDown(d);

		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Scene& scene = *scenes_[activeScene_];
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
