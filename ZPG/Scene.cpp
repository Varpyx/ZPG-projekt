#include "Scene.h"

ShaderProgram* Scene::addShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	programs_.push_back(ShaderProgram(vertexFile, fragmentFile));
	return &programs_.back();
}

void Scene::addDrawableObject(Model model, ShaderProgram* shaderProgram)
{
	objects_.push_back(DrawableObject(model, shaderProgram));
}

void Scene::draw() const
{
	for (const DrawableObject& object : objects_)
		object.draw();
}