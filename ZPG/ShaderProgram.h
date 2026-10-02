#pragma once

// Include GLAD
#include <glad/gl.h>

// Include GLM
#include <glm/glm.hpp>

#include "Shader.h"

#include <string>
#include <unordered_map>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	bool use() const;

	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, const glm::vec3& value);
	void setUniform(const char* name, const glm::mat4& value);

private:
	// Vrati location uniformu, nebo -1 pokud v shader programu neni.
	// Location se hleda jen jednou, vysledek se cachuje.
	GLint uniformLocation(const char* name);

	Shader vertexShader_;
	Shader fragmentShader_;
	GLuint id_ = 0;
	std::unordered_map<std::string, GLint> uniformLocations_;
};