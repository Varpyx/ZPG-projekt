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

Light* Scene::addLight(const glm::vec3& position, const glm::vec4& color, const glm::vec4& ambient)
{
	lights_.push_back(std::make_unique<Light>(position, color, ambient));
	return lights_.back().get();
}

void Scene::update(float deltaTime)
{
	for (DrawableObject& object : objects_) {
		object.update(deltaTime);
	}
}

void Scene::draw()
{
	for(auto& program : programs_) {
		program->use();
		
		for(auto& light : lights_) {
			program->setUniform("lightPos", light->getPosition());
			program->setUniform("lightColor", light->getColor());
			program->setUniform("ambient", light->getAmbient());
		}
	}

	for (DrawableObject& object : objects_) {
		object.draw();
	}
}

