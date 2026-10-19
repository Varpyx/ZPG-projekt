#include "ShaderProgram.h"

// Include GLAD
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

ShaderProgram::ShaderProgram(const char* vertexFile, const char* fragmentFile)
	: vertexShader_(GL_VERTEX_SHADER, vertexFile),
	fragmentShader_(GL_FRAGMENT_SHADER, fragmentFile)
{
	// Create and link the shader program
	id_ = glCreateProgram();
	glAttachShader(id_, vertexShader_.getId());
	glAttachShader(id_, fragmentShader_.getId());
	glLinkProgram(id_);

	// Check linking status
	int success;
	glGetProgramiv(id_, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(id_, sizeof(infoLog), nullptr, infoLog);
		std::cout
			<< "Shader program failed:\n"
			<< infoLog << std::endl;
	}
}

bool ShaderProgram::use() const
{
	if (id_ == 0)
		return false;

	glUseProgram(id_);
	return true;
}

void ShaderProgram::onCameraChanged(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPos)
{
	viewMatrix_ = viewMatrix;
	projectionMatrix_ = projectionMatrix;
	cameraPos_ = cameraPos;
	camChanged_ = true;
}

void ShaderProgram::updateCameraUniforms()
{
	if (camChanged_)
	{
		setUniform("viewMatrix", viewMatrix_);
		setUniform("projectionMatrix", projectionMatrix_);
		setUniform("cameraPos", cameraPos_);
		camChanged_ = false;
	}
}


void ShaderProgram::setUniform(const char* name, float value)
{
	GLint location = glGetUniformLocation(id_, name);
	if (location == -1)
		return;

	glUniform1f(location, value);
}

void ShaderProgram::setUniform(const char* name, int value)
{
	GLint location = glGetUniformLocation(id_, name);
	if (location == -1)
		return;

	glUniform1i(location, value);
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(id_, name);
	if (location == -1)
		return;

	glUniform3fv(location, 1, &value[0]);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& value)
{
	GLint location = glGetUniformLocation(id_, name);
	if (location == -1)
		return;

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::setUniform(const char* name, const glm::vec4& value)
{
	GLint location = glGetUniformLocation(id_, name);
	if (location == -1)
		return;
	glUniform4fv(location, 1, &value[0]);
}
