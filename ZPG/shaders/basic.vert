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
    //change scale
    vec3 p = position * scale;

    //rotate around y axis
    float c = cos(angleY);
    float s = sin(angleY);
    // x' =  cos(a)*x + sin(a)*z
    // y' =  y
    // z' = -sin(a)*x + cos(a)*z
    p = vec3(c*p.x + s*p.z, p.y, -s*p.x + c*p.z);

    //rotate around plane XY
    c = cos(anglePlaneXY);
    s = sin(anglePlaneXY);
    // x' =  x*cos(a) - y*sin(a)
    // y' =  x*sin(a) + y*cos(a)
    p = vec3(c*p.x - s*p.y, s*p.x + c*p.y, p.z);

    p += offset;

    vertexColor = color;
    gl_Position = vec4(p, 1.0);
}