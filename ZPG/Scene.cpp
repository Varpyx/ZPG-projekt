#include "Scene.h"

ShaderProgram* Scene::addShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	programs_.push_back(ShaderProgram(vertexFile, fragmentFile));
	return &programs_.back();
}

void Scene::addDrawableObject(Model model, ShaderProgram* shaderProgram,
	const glm::vec3& color, float scale, const glm::vec3& offset)
{
	objects_.push_back(DrawableObject(model, shaderProgram, color, scale, offset));
}

void Scene::update(float deltaTime)
{
	for (DrawableObject& object : objects_)
		object.update(deltaTime);
}

void Scene::draw()
{
	for (DrawableObject& object : objects_)
		object.draw();
}