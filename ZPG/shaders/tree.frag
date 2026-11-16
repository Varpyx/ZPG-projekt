#version 330 core

#define MAX_LIGHTS 10

struct Light {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
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

float attenuation(float d, float c, float l, float q)
{
    // d = distance from the light to the fragment
    // c = constant attenuation factor
    // l = linear attenuation factor
    // q = quadratic attenuation factor
    float att=1.0/ (c + l*d + q*d*d);
    return clamp(att , 0.0 , 1.0);
}

void main(void)
{
    // norm vectors
    vec3 norm = normalize(worldNorm);
    vec3 viewDir = normalize(cameraPos - worldPos);

    vec3 color = useColor ? vertexColor : fragmentColor;

    // ambient
    vec3 result = ambient.rgb * color;

    for(int i = 0; i < numberOfLights; i++) {
        float dist = length(lights[i].position.xyz - worldPos);
        //direction of light
        vec3 lightDir = normalize(lights[i].position.xyz - worldPos);

        float att = attenuation(dist, 1.0, 0.8, 0.2);
    
        // diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        result += att* diff * lights[i].diffuse.rgb * color;

        // spec
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

        // light source on the wrong side?
        if (dot(norm, lightDir) < 0.0) {
            spec = 0.0;
        }

        result += att * spec * lights[i].specular.rgb; 
    }

    //I = Ia + Id + Is
    fragColor = vec4(result, 1.0);
}

