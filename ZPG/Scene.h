#pragma once

#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Skybox.h"

// Include GLM
#include <glm/glm.hpp>

#include <vector>
#include <memory>

//Michal Poncza
class Scene
{
public:
	Scene(Camera camera = Camera()) : camera_(camera) {}
	~Scene();

	ShaderProgram* addShaderProgram(const char* vertexFile, const char* fragmentFile);
	DrawableObject& addDrawableObject(Model model, Material material, float scale = 1.0f, glm::vec3 offset = glm::vec3(0.2f), float speed = 0.0f, glm::vec3 velocity = glm::vec3(0.0f));
	Light* addLight(glm::vec3 position = glm::vec3(0.0f), glm::vec4 diffuse = glm::vec4(1.0f), glm::vec4 specular = glm::vec4(1.0f), int type = 1, glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f));

	void update(float deltaTime);
	void draw();
	void drawSkybox();
	void createSkybox(const char* posX, const char* negX, const char* posY, const char* negY, const char* posZ, const char* negZ);

	void removeObject(size_t index);
	Camera& getCamera() { return camera_; }
	
	void addTree(glm::vec3 position);
	void rotateObject(int index);
	void scaleObject(int index);
	void startParametricLine(glm::vec3 start, glm::vec3 end, float speed = 0.2f);
	void startCubicLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float speed = 0.2f);
	void setAmbient(glm::vec4 ambientColor) { ambient_ = ambientColor; }
	void toggleFlashlight() { flashlightOn_ = !flashlightOn_; }
private:
	std::vector<std::unique_ptr<ShaderProgram>> programs_;
	std::vector<std::unique_ptr<DrawableObject>> objects_;
	std::vector<std::unique_ptr<Light>> lights_;
	Camera camera_;
	Skybox* skybox_ = nullptr;
	ShaderProgram* treeShader_ = nullptr;
	glm::vec4 ambient_ = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	bool flashlightOn_ = false;
};