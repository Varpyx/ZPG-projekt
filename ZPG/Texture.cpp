#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"
#include <cstdio>

//function from LMS to load texture
Texture::Texture(const char* path)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width_, &height_, nullptr, 4);
	if (!data) {
		printf("Texture load failed (%s): %s\n", path, stbi_failure_reason());
		return;
	}

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &textureID_);
	glBindTexture(GL_TEXTURE_2D, textureID_);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}