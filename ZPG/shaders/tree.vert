#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform vec3 fragmentColor;

out vec3 worldPos;
out vec3 worldNorm;
out vec3 vertexColor;

void main()
{
    worldPos = vec3(modelMatrix* vec4(vp, 1.0));
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

    if(gl_VertexID>36443)   
	    vertexColor = fragmentColor;
    else 
	    vertexColor = vec3(1.f, 0.f, 0.f);  
        
    worldNorm = normalize(normalMatrix * vn);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);

}
    
