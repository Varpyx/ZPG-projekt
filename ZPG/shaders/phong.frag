#version 330 core

in vec3 worldPos;
in vec3 worldNorm;
out vec4 fragColor;

uniform vec3 lightPos;   
uniform vec3 cameraPos;
uniform vec4 lightColor; 
uniform vec4 ambient;

uniform vec3 fragmentColor;

void main(void)
{
    // norm vectors
    vec3 norm = normalize(worldNorm);
    vec3 lightDir = normalize(lightPos - worldPos);
    vec3 viewDir = normalize(cameraPos - worldPos);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor.rgb * fragmentColor;

    // spec
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
    vec3 specular = spec * lightColor.rgb; 

    // ambient
    vec3 amb = ambient.rgb * fragmentColor;

    // light source on the wrong side?
    if (dot(norm, lightDir) < 0.0) {
        specular = vec3(0.0, 0.0, 0.0);
    }

    //I = Ia + Id + Is
    vec3 result = amb + diffuse + specular;

    fragColor = vec4(result, 1.0);
}