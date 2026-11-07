#pragma once

// Include GLAD
#include <glad/gl.h>

//Michal Poncza
class Model
{
public:
	// attribute layout: 0 = position, 1 = normal, 2 = color, 3 = uv
	Model(const float* data, unsigned int vertexCount, unsigned int floatPerVertex = 6, bool hasNormal = true, bool hasColor = true, bool coloreBeforeNormal = false, bool hasUV = false);
	void draw();

private:
	GLuint vao_ = 0;
	unsigned int vertexCount_ = 0;
};