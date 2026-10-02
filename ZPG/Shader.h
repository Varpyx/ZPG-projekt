#pragma once

// Include GLAD
#include <glad/gl.h>

class Shader
{
public:
	Shader() = default;
	Shader(GLenum type, const char* file);
	GLuint getId() const { return id_; }

private:
	GLuint id_ = 0;
};