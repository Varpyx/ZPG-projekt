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
    vec3 diffuse = diff * lightColor.rgb;

    vec3 amb = ambient.rgb;
    
    vec3 result = (amb + diffuse) * fragmentColor;
    fragColor = vec4(result, 1.0);
}