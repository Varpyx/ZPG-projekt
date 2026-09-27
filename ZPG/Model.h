#pragma once

class Model
{
public:
	// data holds 6 floats per vertex: position xyz, then normal xyz.
	Model(const float* data, unsigned int vertexCount);

	void draw() const;

private:
	unsigned int vao_ = 0;
	unsigned int vertexCount_ = 0;
};
