#include "Scene.h"

ShaderProgram* Scene::addShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	programs_.push_back(std::make_unique<ShaderProgram>(vertexFile, fragmentFile));
	camera_.addObserver(programs_.back().get());
	return programs_.back().get();
}

DrawableObject& Scene::addDrawableObject(Model model, ShaderProgram* shaderProgram,
	const glm::vec3& color, float scale, const glm::vec3& offset, float speed, const glm::vec3& velocity)
{
	objects_.push_back(DrawableObject(model, shaderProgram, color, scale, offset, speed, velocity));
	return objects_.back();
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

