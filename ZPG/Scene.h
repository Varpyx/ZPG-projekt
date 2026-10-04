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

private:
	// deque, ne vector: pri push_back neprevede existujici prvky,
	// takze ukazatele v DrawableObject zustavaji platne
	std::deque<ShaderProgram> programs_;
	std::vector<DrawableObject> objects_;
};