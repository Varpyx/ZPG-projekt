#version 330 core

in vec3 worldPos;
in vec3 worldNorm;
in vec3 vertexColor;
out vec4 fragColor;

uniform vec3 lightPos;   
uniform vec3 cameraPos;
uniform vec4 lightColor; 
uniform vec4 ambient;

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
    float dist = length(lightPos - worldPos);
    vec3 norm = normalize(worldNorm);
    vec3 lightDir = normalize(lightPos - worldPos);
    vec3 viewDir = normalize(cameraPos - worldPos);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor.rgb * vertexColor;

    // spec
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * lightColor.rgb; 

    // ambient
    vec3 amb = ambient.rgb * vertexColor;

    // light source on the wrong side?
    if (dot(norm, lightDir) < 0.0) {
        specular = vec3(0.0, 0.0, 0.0);
    }

    float att = attenuation(dist, 1.0, 0.8, 0.2);
    //I = Ia + Id + Is
    vec3 result = amb + diffuse + specular;

    fragColor = vec4(att*result, 1.0);
}

