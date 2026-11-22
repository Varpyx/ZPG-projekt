#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 vUV;
out vec3 worldPos;
out vec3 worldNorm;

void main()
{
    worldPos = vec3(modelMatrix* vec4(position, 1.0));
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
        
    worldNorm = normalize(normalMatrix * normal);

    vUV = uv;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
