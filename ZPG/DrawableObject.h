#pragma once

#include "Model.h"
#include "Material.h"
#include "Transformation.h"

// Include GLM
#include <glm/glm.hpp>
#include <memory>

//Michal Poncza
class DrawableObject
{
public:
	DrawableObject(Model model, Material material,
		float scale = 1.0f, glm::vec3 offset = glm::vec3(0.0f), float speed = 0.0f, glm::vec3 velocity = glm::vec3(0.0f));
	
	void update(float deltaTime);
	void draw();

	void addTransformation(std::unique_ptr<Transformation> transformation);
	void setTransformation(std::unique_ptr<CompositeTransformation> transformation);

	glm::mat4 getModelMatrix();

private:
	Model model_;
	std::unique_ptr<CompositeTransformation> transformation_;
	Material material_;
};