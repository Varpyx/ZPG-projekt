#include "ShaderProgram.h"

// Include GLAD
#include <glad/gl.h>

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

GLint ShaderProgram::uniformLocation(const char* name)
{
	auto it = uniformLocations_.find(name);
	if (it != uniformLocations_.end())
		return it->second;

	// -1 if uniform is not found
	GLint location = glGetUniformLocation(id_, name);
	if (location == -1)
		std::cout << "Uniform '" << name << "' nebyl v shader programu nalezena" << std::endl;

	uniformLocations_.emplace(name, location);
	return location;
}

void ShaderProgram::setUniform(const char* name, float value)
{
	GLint location = uniformLocation(name);
	if (location == -1)
		return;

	glUseProgram(id_);
	glUniform1f(location, value);
}

void ShaderProgram::setUniform(const char* name, int value)
{
	GLint location = uniformLocation(name);
	if (location == -1)
		return;

	glUseProgram(id_);
	glUniform1i(location, value);
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& value)
{
	GLint location = uniformLocation(name);
	if (location == -1)
		return;

	glUseProgram(id_);
	glUniform3fv(location, 1, &value[0]);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& value)
{
	GLint location = uniformLocation(name);
	if (location == -1)
		return;

	glUseProgram(id_);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}