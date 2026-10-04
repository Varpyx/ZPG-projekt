#pragma once

#include "DrawableObject.h"
#include "ShaderProgram.h"

// Include GLM
#include <glm/glm.hpp>

#include <deque>
#include <vector>

class Scene
{
public:
	ShaderProgram* addShaderProgram(const char* vertexFile, const char* fragmentFile);
	void addDrawableObject(Model model, ShaderProgram* shaderProgram,
		const glm::vec3& color = glm::vec3(1.0f), float scale = 1.0f, const glm::vec3& offset = glm::vec3(0.2f));

	void update(float deltaTime);
	void draw();

	// transformations applied to all objects in the scene
	void translateAll(const glm::vec3& delta);
	void rotateYAll(float alpha);
	void rotatePlaneXYAll(float alpha);
	void scaleAll(float deltaScale);

private:
	std::deque<ShaderProgram> programs_;
	std::vector<DrawableObject> objects_;
};