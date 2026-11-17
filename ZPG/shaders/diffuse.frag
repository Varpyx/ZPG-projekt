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
out vec4 fragColor;

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec4 ambient;
uniform vec3 fragmentColor;

float attenuation(float d, float c, float l, float q)
{
    return clamp(1.0 / (c + l * d + q * d * d), 0.0, 1.0);
}

void main(void)
{
    vec3 norm = normalize(worldNorm);
    vec3 result = ambient.rgb;
    
    //Ia + sum(Id)
    for(int i = 0; i < numberOfLights; i++) {
        vec3 lightDir;
        float att;

        // directional light - no attenuation
        if(lights[i].position.w == 0.0) {
            lightDir = normalize(-lights[i].direction.xyz);
            att = 1.0;
        } else {
            float dist = length(lights[i].position.xyz - worldPos);
            //direction of light
            lightDir = normalize(lights[i].position.xyz - worldPos);

            att = attenuation(dist, 1.0, 0.8, 0.2);
        
            //flashlight or reflector
            if (lights[i].position.w == 2.0){
                float alpha = 0.97;
                float dotLF = dot(lightDir, normalize(-lights[i].direction.xyz));
            
                float intensity = clamp((dotLF - alpha) / (1.0 - alpha), 0.0, 1.0);
                att *= intensity;
            }
        }
        float diff = max(dot(lightDir, worldNorm), 0.0);
        result += att * diff * lights[i].diffuse.rgb;
        
    }

    fragColor = vec4(result * fragmentColor, 1.0);
}