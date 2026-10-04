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

void Scene::translateAll(const glm::vec3& delta)
{
	for (DrawableObject& object : objects_)
		object.getTransformation().translate(delta);
}

void Scene::rotateYAll(float alpha)
{
	for (DrawableObject& object : objects_)
		object.getTransformation().rotateY(alpha);
}

void Scene::rotatePlaneXYAll(float alpha)
{
	for (DrawableObject& object : objects_)
		object.getTransformation().rotatePlaneXY(alpha);
}

void Scene::scaleAll(float deltaScale)
{
	for (DrawableObject& object : objects_)
		object.getTransformation().addScale(deltaScale);
}