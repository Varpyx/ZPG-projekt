#pragma once

#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"

// Include GLM
#include <glm/glm.hpp>

#include <vector>
#include <memory>

//Michal Poncza
class Scene
{
public:
	Scene(const Camera& camera = Camera()) : camera_(camera) {}

	ShaderProgram* addShaderProgram(const char* vertexFile, const char* fragmentFile);
	DrawableObject& addDrawableObject(Model model, ShaderProgram* shaderProgram, const glm::vec3& color = glm::vec3(1.0f), float scale = 1.0f, const glm::vec3& offset = glm::vec3(0.2f), float speed = 0.0f, const glm::vec3& velocity = glm::vec3(0.0f));
	Light* addLight(const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& color = glm::vec4(1.0f), const glm::vec4& ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	void update(float deltaTime);
	void draw();

	Camera& getCamera() { return camera_; }

private:
	std::vector<std::unique_ptr<ShaderProgram>> programs_;
	std::vector<DrawableObject> objects_;
	std::vector<std::unique_ptr<Light>> lights_;
	Camera camera_;
};