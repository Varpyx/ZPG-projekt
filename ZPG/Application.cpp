// Include GLAD
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
#include "Models/tree.h"
#include "Models/login2.h"
#include "Models//sun.h"
#include "Models/earth.h"	
#include "Models/moon.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>

//fuctions from example code
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

//Michal Poncza
void Application::keyCallback(GLFWwindow* window, int key, int scancodes, int action, int mods)
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

	// reserve - preallocate memory for 5 scenes to avoid reallocations
	scenes_.reserve(5);

	// Scena 1: suzi
	Scene* scene1 = &scenes_.emplace_back();
	ShaderProgram* mesh1 = scene1->addShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* loginShader1 = scene1->addShaderProgram("shaders/basic.vert", "shaders/login.frag");
	scene1->addDrawableObject(
		Model(suziSmooth, sizeof(suziSmooth) / (6 * sizeof(float))), mesh1,
		glm::vec3(1.0f, 0.7f, 0.2f), 0.4f, glm::vec3(0.0f), 15.0f, glm::vec3(0.1f, 0.0f, 0.0f));
	scene1->addDrawableObject(
		Model(login2, sizeof(login2) / (6 * sizeof(float))), loginShader1,
		glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, glm::vec3(0.8f, -0.8f, 0.0f));

	// Scena 2: sphere
	Scene* scene2 = &scenes_.emplace_back();
	ShaderProgram* mesh2 = scene2->addShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* loginShader2 = scene2->addShaderProgram("shaders/basic.vert", "shaders/login.frag");
	scene2->addDrawableObject(
		Model(sphere, 2880), mesh2,
		glm::vec3(0.4f, 0.6f, 1.0f), 0.4f, glm::vec3(0.3f, 0.0f, 0.0f));
	scene2->addDrawableObject(
		Model(login2, sizeof(login2) / (6 * sizeof(float))), loginShader2,
		glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, glm::vec3(0.8f, -0.8f, 0.0f));

	// Scena 3: bushes and trees
	Scene* scene3 = &scenes_.emplace_back();
	ShaderProgram* mesh3 = scene3->addShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* flat3 = scene3->addShaderProgram("shaders/basic.vert", "shaders/basic2.frag");
	ShaderProgram* loginShader3 = scene3->addShaderProgram("shaders/basic.vert", "shaders/login.frag");

	srand(3);
	for(int i = 0; i < 20; i++)
	{
		float bx = -0.7f + 2.0f * rand() / RAND_MAX;
		float by = -0.9f + 1.2f * rand() / RAND_MAX;
		DrawableObject& bush = scene3->addDrawableObject(Model(bushes, 8730), mesh3, glm::vec3(0.6f, 1.0f, 0.5f));
		auto bt = std::make_unique<CompositeTransformation>();
		bt->addTransformation(std::make_unique<Translation>(glm::vec3(bx, by, 0.1f)));
		bt->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 360.0f * rand() / RAND_MAX));
		bt->addTransformation(std::make_unique<Scale>(0.3f));
		bush.setTransformation(std::move(bt));

		bx = -0.9f + 2.0f * rand() / RAND_MAX;
		by = -0.9f + 1.2f * rand() / RAND_MAX;
		DrawableObject& trees = scene3->addDrawableObject(Model(tree, 92814), mesh3, glm::vec3(0.6f, 1.0f, 0.5f));
		auto tt = std::make_unique<CompositeTransformation>();
		tt->addTransformation(std::make_unique<Translation>(glm::vec3(bx, by, 0.1f)));
		tt->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 360.0f * rand() / RAND_MAX));
		tt->addTransformation(std::make_unique<Scale>(0.05f));
		trees.setTransformation(std::move(tt));
		
	}
	scene3->addDrawableObject(Model(sphere, 2880), flat3, glm::vec3(1.0f, 0.6f, 0.0f), 0.2f, glm::vec3(0.7f, 0.7f, 0.1f));
	scene3->addDrawableObject(
		Model(login2, sizeof(login2) / (6 * sizeof(float))), loginShader3,
		glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, glm::vec3(0.8f, -0.8f, 0.0f));

	//Scena 4: login
	Scene* scene4 = &scenes_.emplace_back();
	ShaderProgram* loginShader4 = scene4->addShaderProgram("shaders/basic.vert", "shaders/login.frag");
	scene4->addDrawableObject(
		Model(login2, sizeof(login2) / (6 * sizeof(float))), loginShader4,
		glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

	//Scene 5: planets
	Scene* scene5 = &scenes_.emplace_back();
	ShaderProgram* mesh5 = scene5->addShaderProgram("shaders/basic.vert", "shaders/basic.frag");
	ShaderProgram* login5 = scene5->addShaderProgram("shaders/basic.vert", "shaders/login.frag");	

	DrawableObject& Sun = scene5->addDrawableObject(
		Model(sun, 11520, 9), mesh5,
		glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);

	
	DrawableObject& Earth = scene5->addDrawableObject(
		Model(earth, 11520, 9), mesh5,
		glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, glm::vec3(0.0f, 0.0f, 0.0f));

	auto et = std::make_unique<CompositeTransformation>();
	et->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 10.0f));
	et->addTransformation(std::make_unique<Translation>(glm::vec3(-0.7f, 0.0f, 0.0f)));
	et->addTransformation(std::make_unique<Scale>(0.1f));
	Earth.setTransformation(std::move(et));

	DrawableObject& Moon = scene5->addDrawableObject(
		Model(moon, 11520, 9), mesh5,
		glm::vec3(1.0f, 1.0f, 1.0f), 0.05f, glm::vec3(0.0f, 0.0f, 0.0f));

	auto earthPom = std::make_unique<CompositeTransformation>();
	earthPom->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 10.0f));
	earthPom->addTransformation(std::make_unique<Translation>(glm::vec3(-0.7f, 0.0f, 0.0f)));

	auto mt = std::make_unique<CompositeTransformation>();
	mt->addTransformation(std::move(earthPom));
	mt->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, 60.0f));
	mt->addTransformation(std::make_unique<Translation>(glm::vec3(-0.2f, 0.0f, 0.0f)));
	mt->addTransformation(std::make_unique<Scale>(0.05f));
	Moon.setTransformation(std::move(mt));

	printf("Created %zu scenes, change them with 1-%zu\n", scenes_.size(), scenes_.size());
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