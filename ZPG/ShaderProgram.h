#pragma once

// Include GLAD
#include <glad/gl.h>

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram(const char* vertexFile, const char* fragmentFile);
	bool use() const;

private:
	Shader vertexShader_;
	Shader fragmentShader_;
	GLuint id_ = 0;
};