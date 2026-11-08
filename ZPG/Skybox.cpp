#include "Skybox.h"

#include <glad/gl.h>
#include <stb_image.h>
#include <cstdio>

#include "Camera.h"

namespace
{
    const float skyboxVertices[] =
    {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
}

Skybox::Skybox(const char* posX, const char* negX,
    const char* posY, const char* negY,
    const char* posZ, const char* negZ)
    : shaderProgram_("shaders/skybox.vert", "shaders/skybox.frag"),
    cube_(skyboxVertices, 36, 3, false, false)
{
    const char* faces[6] = { posX, negX, posY, negY, posZ, negZ };

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &cubemapID_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID_);

    stbi_set_flip_vertically_on_load(false);

    int width, height, nrChannels;
    unsigned char* data;
    for (int i = 0; i < 6; i++)
    {
        data = stbi_load(faces[i], &width, &height, &nrChannels, 3);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            printf("Cubemap texture failed to load at path: %s\n", faces[i]);
            stbi_image_free(data);
        }
    }

    stbi_set_flip_vertically_on_load(true);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::draw(Camera& camera)
{
    glDepthMask(GL_FALSE); 

    shaderProgram_.use();
    shaderProgram_.setUniform("viewMatrix", camera.getViewMatrix());
    shaderProgram_.setUniform("projectionMatrix", camera.getProjectionMatrix());
    shaderProgram_.setUniform("skybox", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID_);

    cube_.draw();

    glDepthMask(GL_TRUE); 
}
