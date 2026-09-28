#pragma once

class Model
{
public:
	Model(const float* data, unsigned int vertexCount);
	void draw() const;

private:
	unsigned int vao_ = 0;
	unsigned int vertexCount_ = 0;
};
