#pragma once

#include <glad/gl.h>

class Texture
{
public:

	Texture(const char* path);

	GLuint getID() { return textureID_; }
	int getWidth() { return width_; }
	int getHeight() { return height_; }
private:
	GLuint textureID_ = 0;
	int width_ = 0;
	int height_ = 0;
};