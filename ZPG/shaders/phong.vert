#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 fragmentColor;

out vec3 worldPos;
out vec3 worldNorm;

void main()
{
    worldPos = vec3(modelMatrix* vec4(vp, 1.0));
    //worldNorm = vn.xyz / vn.w;
    worldNorm = vn;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);

}