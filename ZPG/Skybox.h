#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Model.h"
#include "ShaderProgram.h"

class Camera;

class Skybox
{
public:
    Skybox(const char* posX, const char* negX,
        const char* posY, const char* negY,
        const char* posZ, const char* negZ);

    void draw(Camera& camera);

private:
    GLuint cubemapID_ = 0;
    ShaderProgram shaderProgram_;
    Model cube_;
};
