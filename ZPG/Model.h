#pragma once

// Include GLAD
#include <glad/gl.h>

//Michal Poncza
class Model
{
public:
	Model(const float* data, unsigned int vertexCount, unsigned int floatPerVertex = 6, bool hasNormal = true, bool hasColor = true, bool coloreBeforeNormal = false);
	void draw() const;

private:
	GLuint vao_ = 0;
	unsigned int vertexCount_ = 0;
};