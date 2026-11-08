#pragma once

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Texture.h"

class Material
{
public:
	Material(ShaderProgram* shaderProgram, glm::vec3 color = glm::vec3(1.0f));

	void setTexture(Texture* texture, int textureUnit);
	void bind();

	ShaderProgram* getShaderProgram() { return shaderProgram_; }
	glm::vec3 getColor() { return color_; }

private:
	ShaderProgram* shaderProgram_ = nullptr;
	GLuint textureID_ = 0;
	int textureUnit_ = 0;
	glm::vec3 color_ = glm::vec3(1.0f);
};