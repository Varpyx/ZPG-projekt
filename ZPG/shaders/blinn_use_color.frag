#version 330 core

in vec3 worldPos;
in vec3 worldNorm;
in vec3 vertexColor;

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

    //hlafway vector
    vec3 halfwayDir = normalize(lightDir + viewDir);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor.rgb * vertexColor;

    // spec
    float spec = pow(max(dot(halfwayDir, norm), 0.0), 64.0);
    vec3 specular = spec * lightColor.rgb; 

    // light source on the wrong side?
    if (dot(norm, lightDir) < 0.0) {
        specular = vec3(0.0, 0.0, 0.0);
    }

    // ambient
    vec3 amb = ambient.rgb * vertexColor;

    //I = Ia + Id + Is
    vec3 result = amb + diffuse + specular;

    fragColor = vec4(result, 1.0);
}