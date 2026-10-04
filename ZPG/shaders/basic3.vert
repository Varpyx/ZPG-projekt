#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform float scale;
uniform vec3 offset;
uniform float angleY;
uniform float anglePlaneXY;

out vec3 vertexColor;

void main()
{
    vec3 p = position * scale;

    float c = cos(angleY);
    float s = sin(angleY);

    p = vec3(c*p.x + s*p.z, p.y, -s*p.x + c*p.z);

    c = cos(anglePlaneXY);
    s = sin(anglePlaneXY);

    p = vec3(c*p.x - s*p.y, s*p.x + c*p.y, p.z);

    p += offset;

    vertexColor = color;
    gl_Position = vec4(p, 1.0);
}