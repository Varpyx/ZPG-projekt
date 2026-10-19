#pragma once
#include <glm/glm.hpp>

class Light {
public:
	Light(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4 ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f))
		: position_(position), color_(color), ambient_(ambient) {}

	void setPosition(glm::vec3 position) { position_ = position; }
	void setColor(glm::vec4 color) { color_ = color; }
	void setAmbient(glm::vec4 ambient) { ambient_ = ambient; }

	glm::vec3 getPosition() { return position_; }
	glm::vec4 getColor() { return color_; }
	glm::vec4 getAmbient() { return ambient_; }
private:
	glm::vec3 position_;
	glm::vec4 color_;
	glm::vec4 ambient_;
};
