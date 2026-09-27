#include "Shader.h"

// Include GLAD
#include <glad/gl.h>

#include <stdlib.h>
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>

// Compiles one shader of the given type and returns its id
static GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile)
{
	// Creates an empty shader
	unsigned int shaderID = glCreateShader(shaderType);

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
	GLint success;
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

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Create and compile the vertex and fragment shaders
	GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, vertexFile);
	GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, fragmentFile);

	// Create and link the shader program
	id_ = glCreateProgram();
	glAttachShader(id_, fragmentShader);
	glAttachShader(id_, vertexShader);
	glLinkProgram(id_);
}

void Shader::use() const
{
	glUseProgram(id_);
}
