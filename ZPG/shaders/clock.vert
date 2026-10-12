#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float angleSeconds;
uniform float angleMinutes;
uniform float angleHours;

out vec3 vertexColor;

void main()
{
    vec3 pos = position;

    if (color == vec3(1.0, 0.0, 0.0)){ //seconds
        float c = cos(angleSeconds);
        float s = sin(angleSeconds);
        pos.x = position.x * c - position.y * s;
        pos.y = position.x * s + position.y * c;
    } else if (color == vec3(0.0, 0.0, 1.0)){ //minutes
        float c = cos(angleMinutes);
        float s = sin(angleMinutes);
        pos.x = position.x * c - position.y * s;
        pos.y = position.x * s + position.y * c;
    } else if (color == vec3(0.0, 1.0, 0.0)){ //hours
        float c = cos(angleHours);
        float s = sin(angleHours);
        pos.x = position.x * c - position.y * s;
        pos.y = position.x * s + position.y * c;
    }
    vertexColor = color;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);

}