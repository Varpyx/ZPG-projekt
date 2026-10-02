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
    // 1) zmena meritka
    vec3 p = position * scale;

    // 2) rotace v prostoru kolem osy y
    float c = cos(angleY);
    float s = sin(angleY);
    // x' =  cos(a)*x + sin(a)*z
    // y' =  y
    // z' = -sin(a)*x + cos(a)*z
    p = vec3(c*p.x + s*p.z, p.y, -s*p.x + c*p.z);

    // 3) rotace v rovine xy kolem pocatku
    c = cos(anglePlaneXY);
    s = sin(anglePlaneXY);
    // x' =  x*cos(a) - y*sin(a)
    // y' =  x*sin(a) + y*cos(a)
    p = vec3(c*p.x - s*p.y, s*p.x + c*p.y, p.z);

    // 4) posun (translace)
    p += offset;

    vertexColor = color;
    gl_Position = vec4(p, 1.0);
}