#pragma once

#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

// Include GLM
#include <glm/glm.hpp>
#include <memory>

class DrawableObject
{
public:
	DrawableObject(Model model, ShaderProgram* shaderProgram,
		const glm::vec3& color = glm::vec3(1.0f), float scale = 1.0f, const glm::vec3& offset = glm::vec3(0.0f), float speed = 0.0f, const glm::vec3& velocity = glm::vec3(0.0f));
	
	void update(float deltaTime);
	void draw();

	void addTransformation(std::unique_ptr<Transformation> transformation);
	void setTransformation(std::unique_ptr<CompositeTransformation> transformation);

	glm::mat4 getModelMatrix();

private:
	Model model_;
	std::unique_ptr<CompositeTransformation> transformation_;
	ShaderProgram* shaderProgram_ = nullptr;
	glm::vec3 color_;
};