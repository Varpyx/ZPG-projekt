#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec3 vc;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldPos;
out vec3 worldNorm;
out vec3 vertexColor;

void main()
{
    worldPos = vec3(modelMatrix* vec4(vp, 1.0));
    //worldPos.xyz/worldPos.w; DODělat!!!!
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

    vertexColor = vc;
    worldNorm = normalize(normalMatrix * vn);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);

}