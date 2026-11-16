#version 330 core

#define MAX_LIGHTS 10

struct Light {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
};

in vec3 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec4 ambient;
uniform vec3 fragmentColor;

void main(void)
{
    vec3 norm = normalize(worldNorm);
    vec3 result = ambient.rgb;
    
    //Ia + sum(Id)
    for(int i = 0; i < numberOfLights; i++) {
        vec3 lightDir = normalize(lights[i].position.xyz - worldPos);

        float diff = max(dot(lightDir, worldNorm), 0.0);
        result += diff * lights[i].diffuse.rgb;
        
    }

    fragColor = vec4(result * fragmentColor, 1.0);
}