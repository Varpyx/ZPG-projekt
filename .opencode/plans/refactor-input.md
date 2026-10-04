# Plán: Extrahovat zpracování kláves do funkce processInput

## 1) Application.h
Pøidat deklaraci metody `processInput`:

```cpp
private:
	static void keyCallback(GLFWwindow* window, int key, int scancodes, int action, int mods);
	void switchScene(size_t index);
	void processInput(float deltaTime);

	GLFWwindow* window_ = nullptr;
	std::vector<Scene> scenes_;
	size_t activeScene_ = 0;
```

## 2) Application.cpp
Pøidat implementaci metody `processInput`:

```cpp
void Application::processInput(float deltaTime)
{
	if (scenes_.empty())
		return;

	Scene& scene = scenes_[activeScene_];

	const float moveSpeed = 200.0f;
	const float rotSpeed = 2.0f;
	const float scaleSpeed = 1.5f;

	glm::vec3 move(0.0f);
	if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) move.y += 1.0f;
	if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) move.y -= 1.0f;
	if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) move.x -= 1.0f;
	if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) move.x += 1.0f;
	if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS) move.z += 1.0f;
	if (glfwGetKey(window_, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) move.z -= 1.0f;
	if (glm::length(move) > 0.0f)
		scene.translateAll(move * moveSpeed * deltaTime);

	float rotY = 0.0f;
	if (glfwGetKey(window_, GLFW_KEY_Q) == GLFW_PRESS) rotY -= 1.0f;
	if (glfwGetKey(window_, GLFW_KEY_E) == GLFW_PRESS) rotY += 1.0f;
	if (rotY != 0.0f)
		scene.rotateYAll(rotY * rotSpeed * deltaTime);

	float rotXY = 0.0f;
	if (glfwGetKey(window_, GLFW_KEY_Z) == GLFW_PRESS) rotXY -= 1.0f;
	if (glfwGetKey(window_, GLFW_KEY_C) == GLFW_PRESS) rotXY += 1.0f;
	if (rotXY != 0.0f)
		scene.rotatePlaneXYAll(rotXY * rotSpeed * deltaTime);

	float scaleDelta = 0.0f;
	if (glfwGetKey(window_, GLFW_KEY_R) == GLFW_PRESS) scaleDelta += 1.0f;
	if (glfwGetKey(window_, GLFW_KEY_F) == GLFW_PRESS) scaleDelta -= 1.0f;
	if (scaleDelta != 0.0f)
		scene.scaleAll(scaleDelta * scaleSpeed * deltaTime);
}
```

## 3) Application::run()
Nahradit blok voláním `processInput(deltaTime)`:
```cpp
processInput(deltaTime);
```
