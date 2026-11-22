#pragma once
#include <glm/glm.hpp>

class DrawableObject;

class Light {
public:
	Light(glm::vec3 position = glm::vec3(0.0f), glm::vec4 diffuse = glm::vec4(1.0f), glm::vec4 specular = glm::vec4(1.0f), int type = 1, glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3 att = glm::vec3(1.0f, 0.8f, 0.2f))
		: position_(position), diffuse_(diffuse), specular_(specular), type_(type), direction_(direction) , att_(att){}

	void setPosition(glm::vec3 position) { position_ = position; }
	void setDiffuse(glm::vec4 diffuse) { diffuse_ = diffuse; }
	void setSpecular(glm::vec4 spec) { specular_ = spec; }
	void setDirection(glm::vec3 direction) { direction_ = direction; }
	void setObject(DrawableObject* object) { object_ = object; }
	void setAtt(glm::vec3 att) { att_ = att; }

	glm::vec3 getPosition() { return position_; }
	glm::vec3 getAtt() { return att_; }
	glm::vec4 getDiffuse() { return diffuse_; }
	glm::vec4 getSpecular() { return specular_; }
	glm::vec3 getDirection() { return direction_; }
	int getType() { return type_; }
	DrawableObject* getObject() { return object_; }
private:
	glm::vec3 position_;
	glm::vec3 att_;
	glm::vec4 diffuse_;
	glm::vec4 specular_;
	int type_;
	glm::vec3 direction_;
	DrawableObject* object_ = nullptr;
};
