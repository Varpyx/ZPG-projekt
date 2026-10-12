#include "DrawableObject.h"

// Include GLM
#include <glm/gtc/constants.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <ctime>

DrawableObject::DrawableObject(Model model, ShaderProgram* shaderProgram,
	const glm::vec3& color, float scale, const glm::vec3& offset, float speed, const glm::vec3& velocity)
	: model_(model), shaderProgram_(shaderProgram), color_(color)
{
	transformation_ = std::make_unique<CompositeTransformation>();
	//transformation_->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 0.0f, 1.0f), 0.0f, speed));
	transformation_->addTransformation(std::make_unique<Translation>(offset, velocity));
	transformation_->addTransformation(std::make_unique<Rotation>(glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, speed));
	transformation_->addTransformation(std::make_unique<Scale>(scale));
}

void DrawableObject::addTransformation(std::unique_ptr<Transformation> transformation)
{
	transformation_->addTransformation(std::move(transformation));
}

void DrawableObject::setTransformation(std::unique_ptr<CompositeTransformation> transformation)
{
	transformation_ = std::move(transformation);
}

void DrawableObject::update(float deltaTime)
{
	transformation_->update(deltaTime);
}

glm::mat4 DrawableObject::getModelMatrix()
{
	return transformation_->getModelMatrix();
}

void DrawableObject::draw()
{
	if (!shaderProgram_ || !shaderProgram_->use())
		return;

	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	//viewMatrix = glm::lookAt(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//projectionMatrix = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	//getting the time
	std::time_t t = std::time(nullptr);
	std::tm now; // Vytvoøíme normální promìnnou (už to není ukazatel)
	localtime_s(&now, &t);

	// Plynulý výpoèet (aby se ruèièka neposunula jen trhnutím každou minutu/hodinu)
	float seconds = now.tm_sec;
	float minutes = now.tm_min + (seconds / 60.0f);
	float hours = (now.tm_hour % 12) + (minutes / 60.0f);

	// --- 2. VÝPOÈET ÚHLÙ (radiány do mínusu pro rotaci po smìru hodin) ---
	float pi = glm::pi<float>();
	float angleSeconds = -seconds * (2.0f * pi / 60.0f);
	float angleMinutes = -minutes * (2.0f * pi / 60.0f);
	float angleHours = -hours * (2.0f * pi / 12.0f);

	shaderProgram_->setUniform("angleSeconds", angleSeconds);
	shaderProgram_->setUniform("angleMinutes", angleMinutes);
	shaderProgram_->setUniform("angleHours", angleHours);

	shaderProgram_->setUniform("modelMatrix", getModelMatrix());
	shaderProgram_->setUniform("viewMatrix", viewMatrix);
	shaderProgram_->setUniform("projectionMatrix", projectionMatrix);
	shaderProgram_->setUniform("fragmentColor", color_);

	model_.draw();
}

