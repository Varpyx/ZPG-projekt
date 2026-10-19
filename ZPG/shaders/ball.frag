#version 330 core

in vec3 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform vec3 lightPos;   
uniform vec4 lightColor; 
uniform vec4 ambient;

uniform vec3 fragmentColor;

void main(void)
{
    vec3 lightDir = lightPos - worldPos;
    
    float diff = max(dot(normalize(lightDir), normalize(worldNorm)), 0.0);
    vec4 objectColor = vec4(fragmentColor, 1.0);
    
    fragColor = ambient + (diff * objectColor * lightColor);
}