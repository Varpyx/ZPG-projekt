#version 330 core

in vec3 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

void main(void)
{
    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    
    vec3 lightDir = lightPosition - worldPos.xyz;
    
    float diff = max(dot(normalize(lightDir), normalize(worldNorm)), 0.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    
    fragColor = ambient + (diff * objectColor);
}