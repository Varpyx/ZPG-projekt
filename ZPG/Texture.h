#pragma once

#include <glad/gl.h>

class Texture
{
public:

	Texture(char* path);

	GLuint getID(){ return textureID_;}
	int getWidth() { return width_; }
	int getHeight() { return height_; }
private:
	GLuint textureID_;
	int width_;
	int height_;
};