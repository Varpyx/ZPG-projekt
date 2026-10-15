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
    //we are doing SCALE(-1,1,1) hardcoded
    vec3 pos = position;
    pos.x = -pos.x;

    //we are using tempX and tempY so we dont change our pos.x that is scaled
    if (color == vec3(1.0, 0.0, 0.0)){ //seconds
        float c = cos(angleSeconds);
        float s = sin(angleSeconds);
        float tempX = pos.x * c - pos.y * s;
        float tempY = pos.x * s + pos.y * c;
        pos.x = tempX;
        pos.y = tempY;
    } else if (color == vec3(0.0, 0.0, 1.0)){ //hours
        float c = cos(angleHours);
        float s = sin(angleHours);
        float tempX = pos.x * c - pos.y * s;
        float tempY = pos.x * s + pos.y * c;
        pos.x = tempX;
        pos.y = tempY;
    } else if (color == vec3(0.0, 1.0, 0.0)){ //minutes
        float c = cos(angleMinutes);
        float s = sin(angleMinutes);
        float tempX = pos.x * c - pos.y * s;
        float tempY = pos.x * s + pos.y * c;
        pos.x = tempX;
        pos.y = tempY;
    }

    vertexColor = color;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0);

}