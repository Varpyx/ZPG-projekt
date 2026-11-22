#include "Scene.h"
#include "Models/tree.h"
#include "Transformation/Rotation.h"
#include "Transformation/Scale.h"
#include <glm/ext/scalar_constants.hpp>
#include <ctime>
#include <string>

Scene::~Scene()
{
	delete skybox_;
}

ShaderProgram* Scene::addShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	programs_.push_back(std::make_unique<ShaderProgram>(vertexFile, fragmentFile));
	camera_.addObserver(programs_.back().get());
	return programs_.back().get();
}

DrawableObject& Scene::addDrawableObject(Model model, Material material,
	float scale, glm::vec3 offset, float speed, glm::vec3 velocity)
{
	objects_.push_back(std::make_unique<DrawableObject>(model, material, scale, offset, speed, velocity));
	return *objects_.back();
}

Light* Scene::addLight(glm::vec3 position, glm::vec4 diffuse, glm::vec4 specular, int type, glm::vec3 direction)
{
	lights_.push_back(std::make_unique<Light>(position, diffuse, specular, type, direction));
	return lights_.back().get();
}


void Scene::update(float deltaTime)
{
	for (auto& object : objects_) {
		object->update(deltaTime);
	}

	for(auto& light : lights_) { // update position of light if they have moving objects attached
		if (light->getObject() != nullptr) {
			light->setPosition(light->getObject()->getPosition());
		}
	}
}

void Scene::draw()
{
	//getting the time
	std::time_t t = std::time(nullptr);
	std::tm now;
	localtime_s(&now, &t);

	// calc for the smooth effect
	float seconds = static_cast<float>(now.tm_sec);
	float minutes = static_cast<float>(now.tm_min) + (seconds / 60.0f);
	float hours = static_cast<float>(now.tm_hour % 12) + (minutes / 60.0f);

	// calc the angles
	float pi = glm::pi<float>();
	float angleSeconds = seconds * (2.0f * pi / 60.0f);
	float angleMinutes = minutes * (2.0f * pi / 60.0f);
	float angleHours = hours * (2.0f * pi / 12.0f);


	for(auto& program : programs_) {
		program->use();
		//clock
		program->setUniform("angleSeconds", angleSeconds);
		program->setUniform("angleMinutes", angleMinutes);
		program->setUniform("angleHours", angleHours);

		//lights
		program->setUniform("ambient", ambient_);
		if (flashlightOn_) {
			program->setUniform("numberOfLights", static_cast<int>(lights_.size()+1));
		} else {
			program->setUniform("numberOfLights", static_cast<int>(lights_.size()));
		}

		for (int i = 0; i < lights_.size(); i++) {
			std::string baseName = "lights[" + std::to_string(i) + "]";

			//pos + type in vec4
			program->setUniform((baseName + ".position").c_str(), glm::vec4(lights_[i]->getPosition(), 1.0));
			program->setUniform((baseName + ".direction").c_str(), glm::vec4(lights_[i]->getDirection(), 0.0f));
			program->setUniform((baseName + ".diffuse").c_str(), lights_[i]->getDiffuse());
			program->setUniform((baseName + ".specular").c_str(), lights_[i]->getSpecular());
			program->setUniform((baseName + ".type").c_str(), lights_[i]->getType());
			program->setUniform((baseName + ".att").c_str(), lights_[i]->getAtt());
		}

		if (flashlightOn_) {
			std::string baseName = "lights[" + std::to_string(lights_.size()) + "]";
			program->setUniform((baseName + ".position").c_str(), glm::vec4(camera_.getCameraPosition(), 1.0));      
			program->setUniform((baseName + ".direction").c_str(), glm::vec4(camera_.getCameraTarget(), 0.0f));  
			program->setUniform((baseName + ".diffuse").c_str(), glm::vec4(1.0f));
			program->setUniform((baseName + ".specular").c_str(), glm::vec4(1.0f));
			program->setUniform((baseName + ".type").c_str(), 2); // 2 = spot
			program->setUniform((baseName + ".att").c_str(), glm::vec3(1.0,0.3,0.1));
		}

	}

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	int i = 1;
	for (auto& object : objects_) {
		int id = object->canBePicked() ? i : 0;
		glStencilFunc(GL_ALWAYS, static_cast<GLint>(id), 0xFF); 
		glStencilMask(0xFF);
		object->setIndex(id);
		object->draw();
		i++;
	}

	glDisable(GL_STENCIL_TEST);
}

void Scene::drawSkybox()
{
	if(skybox_) {
		skybox_->draw(camera_);
	}
}

void Scene::createSkybox(const char* posX, const char* negX, const char* posY, const char* negY, const char* posZ, const char* negZ)
{
	delete skybox_;
	skybox_ = new Skybox(posX, negX, posY, negY, posZ, negZ);
}

void Scene::removeObject(size_t index)
{
	if (index >= objects_.size())
		return;

	DrawableObject* object = objects_[index].get();

	for (auto& light : lights_) { //if object is connected with light, we set it to zero
		if (light->getObject() == object) {
			light->setObject(nullptr);             
			light->setDiffuse(glm::vec4(0.0f));    
			light->setSpecular(glm::vec4(0.0f));
		}
	}

	objects_.erase(objects_.begin() + index);
	printf("Object at index %zu removed.\n", index);
}

void Scene::addTree(glm::vec3 position)
{
	if(treeShader_ == nullptr) {
		treeShader_ = addShaderProgram("shaders/tree.vert", "shaders/tree.frag");
	}

	Material treeMaterial(treeShader_, glm::vec3(0.3f, 0.8f, 0.2f));
	treeMaterial.setUseColor(true);
	addDrawableObject(Model(tree, 92814, 6, true, false), treeMaterial, 0.01f, position);
	//addDrawableObject(Model(tree, 92814, 6, true, false), treeMaterial, 0.1f, glm::vec3(0.0f, 0.0f, 0.0f));

}

void Scene::rotateObject(int index)
{
	if (index < objects_.size())
		objects_[index]->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 45.0f));
}

void Scene::scaleObject(int index)
{
	if (index < objects_.size())
		objects_[index]->addTransformation(std::make_unique<Scale>(1.2f));
}

void Scene::startParametricLine(glm::vec3 start, glm::vec3 end, float speed)
{
	if (treeShader_ == nullptr)
		treeShader_ = addShaderProgram("shaders/tree.vert", "shaders/tree.frag");

	Material treeMaterial(treeShader_, glm::vec3(0.3f, 0.8f, 0.2f));
	treeMaterial.setUseColor(true);

	DrawableObject& tree1 = addDrawableObject(Model(tree, 92814, 6, true, false), treeMaterial, 0.01f, start);

	tree1.setParametricLine(start, end, speed);
}

