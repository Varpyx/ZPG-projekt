#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vc;
layout (location = 2) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldPos;
out vec3 worldNorm;
out vec3 vertexColor;

void main()
{
    worldPos = vec3(modelMatrix* vec4(vp, 1.0));
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));

    worldNorm = normalize(normalMatrix * vn);
    vertexColor = vc;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);

}