#include "Shader.h"

// Include GLAD
#include <glad/gl.h>

#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>

// Compiles one shader of the given type and returns its id
static GLuint createShaderFromFile(GLenum type, const char* shaderFile)
{
	// Creates an empty shader
	GLuint shaderID = glCreateShader(type);

	if (shaderID == 0)
	{
		std::cout << "Unable to create shader" << std::endl;
		exit(EXIT_FAILURE);
	}

	//Loading the contents of a file into a variable
	std::ifstream file(shaderFile);
	if (!file.is_open())
	{
		std::cout << "Unable to open file " << shaderFile << std::endl;
		glDeleteShader(shaderID);
		exit(-1);
	}
	std::string shaderCode((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	// Set the shader source code
	const char* source = shaderCode.c_str();
	glShaderSource(shaderID, 1, &source, nullptr);

	// Compile the shader source code
	glCompileShader(shaderID);

	// Check specialization/compilation status
	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
		std::cout
			<< "Shader failed:\n"
			<< infoLog << std::endl;
		glDeleteShader(shaderID);
		exit(1);
	}
	return shaderID;
}

Shader::Shader(GLenum type, const char* file)
{
	id_ = createShaderFromFile(type, file);
}