#pragma once

// Include GLAD
#include <glad/gl.h>

class Model
{
public:
	Model(const float* data, unsigned int vertexCount, unsigned int floatPerVertex = 6);
	void draw() const;

private:
	GLuint vao_ = 0;
	unsigned int vertexCount_ = 0;
};