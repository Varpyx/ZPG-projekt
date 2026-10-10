#pragma once

// Include GLAD
#include <glad/gl.h>

// Include GLM
#include <glm/glm.hpp>

#include "Shader.h"

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
	Shader vertexShader_;
	Shader fragmentShader_;
	GLuint id_ = 0;
};