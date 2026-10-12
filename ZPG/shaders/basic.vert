#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vertexColor;

void main()
{
    vertexColor = color;
    //gl_Position = modelMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);

}