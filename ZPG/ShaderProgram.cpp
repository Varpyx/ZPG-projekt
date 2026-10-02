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