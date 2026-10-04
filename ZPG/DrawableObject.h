#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

// Include GLM
#include <glm/glm.hpp>

class DrawableObject
{
public:
	DrawableObject(Model model, ShaderProgram* shaderProgram,
		const glm::vec3& color = glm::vec3(1.0f), float scale = 1.0f, const glm::vec3& offset = glm::vec3(0.0f));

	void update(float deltaTime);
	void draw();

private:
	Model model_;
	Transformation transformation_;
	ShaderProgram* shaderProgram_ = nullptr;
	glm::vec3 color_;
};