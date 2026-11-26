#include "CubicLine.h"
#include "../DrawableObject.h"   // <-- tohle přidat
#include <glm/gtc/matrix_transform.hpp>

CubicLine::CubicLine(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, float speed)
	: speed_(speed), t_(0.0f), direction(1) // Inicializace členských proměnných
{
	A_ = glm::mat4(glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
		glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
		glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
		glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

	B_ = glm::mat4x3(p1, p2, p3, p4);
}

glm::mat4 CubicLine::getModelMatrix()
{
	glm::vec4 parameters = glm::vec4(t_ * t_ * t_, t_ * t_, t_, 1.0f);

	glm::vec3 position = parameters * A_ * glm::transpose(B_);

	return glm::translate(glm::mat4(1.0f), position);
}

void CubicLine::update(float deltaTime)
{
	t_ += direction * speed_ * deltaTime;

	if (t_ >= 1.0f) {
		t_ = 1.0f;
		direction = -1;
	}
	else if (t_ <= 0.0f) {
		t_ = 0.0f;
		direction = 1;
	}
}

void CubicLine::setPoint(int index, glm::vec3 pos)
{
	B_[index] = pos;
}

void CubicLine::setMarkers(std::array<DrawableObject*, 4> markers)
{
	markers_ = markers;
}

void CubicLine::movePoint(int index, glm::vec3 pos)
{
	if (index < 0 || index > 3) return;
	setPoint(index, pos);
	if (markers_[index])
		markers_[index]->setPosition(pos);
}

int CubicLine::findMarkerIndex(DrawableObject* obj)
{
	for (int i = 0; i < 4; i++)
		if (markers_[i] == obj) return i;
	return -1;
}