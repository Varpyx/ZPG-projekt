#version 330 core

layout (location = 0) in vec3 position;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 Pos;

void main()
{
    Pos = position;

    gl_Position = projectionMatrix * mat4(mat3(viewMatrix)) * vec4(position, 1.0);
}