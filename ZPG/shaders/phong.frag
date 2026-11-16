#version 330 core

#define MAX_LIGHTS 10

struct Light {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
    vec4 direction;
};

in vec3 worldPos;
in vec3 worldNorm;
in vec3 vertexColor;
out vec4 fragColor;

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform bool useColor; // if true, use vertexColor, else use fragmentColor
uniform vec3 cameraPos;
uniform vec4 ambient; // amb of the scene

uniform vec3 fragmentColor;

void main(void)
{
    // norm vectors
    vec3 norm = normalize(worldNorm);
    vec3 viewDir = normalize(cameraPos - worldPos);

    vec3 color = useColor ? vertexColor : fragmentColor;

    // ambient
    vec3 result = ambient.rgb * color;

    for(int i = 0; i < numberOfLights; i++) {
        //direction of light
        vec3 lightDir = normalize(lights[i].position.xyz - worldPos);
    
        // diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        result += diff * lights[i].diffuse.rgb * color;

        // spec
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

        // light source on the wrong side?
        if (dot(norm, lightDir) < 0.0) {
            spec = 0.0;
        }

        result += spec * lights[i].specular.rgb; 
    }

    //I = Ia + Id + Is
    fragColor = vec4(result, 1.0);
}