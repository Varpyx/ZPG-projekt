#include "Scene.h"
#include "Models/tree.h"
#include "Transformation/Rotation.h"
#include "Transformation/Scale.h"

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
	objects_.push_back(DrawableObject(model, material, scale, offset, speed, velocity));
	return objects_.back();
}

Light* Scene::addLight(glm::vec3 position, glm::vec4 color, glm::vec4 ambient)
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

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	int i = 1;
	for (DrawableObject& object : objects_) {
		int id = object.canBePicked() ? i : 0;
		glStencilFunc(GL_ALWAYS, static_cast<GLint>(id), 0xFF); 
		glStencilMask(0xFF);
		object.setIndex(id);
		object.draw();
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
	if (index < objects_.size()) {
		objects_.erase(objects_.begin() + index);
		printf("Object at index %zu removed.\n", index);
	}
}

void Scene::addTree(glm::vec3 position)
{
	if(treeShader_ == nullptr) {
		treeShader_ = addShaderProgram("shaders/tree.vert", "shaders/basic.frag");
	}

	Material treeMaterial(treeShader_, glm::vec3(0.3f, 0.8f, 0.2f));
	addDrawableObject(Model(tree, 92814, 6, true, false), treeMaterial, 0.01f, position);
	//addDrawableObject(Model(tree, 92814, 6, true, false), treeMaterial, 0.1f, glm::vec3(0.0f, 0.0f, 0.0f));

}

void Scene::rotateObject(int index)
{
	if (index < objects_.size())
		objects_[index].addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 45.0f));
}

void Scene::scaleObject(int index)
{
	if (index < objects_.size())
		objects_[index].addTransformation(std::make_unique<Scale>(1.2f));
}

void Scene::startParametricLine(int index, glm::vec3 start, glm::vec3 end, float speed)
{
	if(index > 0 && index <= objects_.size())
		objects_[index].setParametricLine(start, end, speed);
}

