#pragma once

// Include GLAD
#include <glad/gl.h>

//Michal Poncza
class Shader
{
public:
	Shader() = default;
	Shader(GLenum type, const char* file);
	GLuint getId() { return id_; }

private:
	GLuint id_ = 0;
};