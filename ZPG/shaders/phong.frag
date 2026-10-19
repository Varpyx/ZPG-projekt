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
	vec3 norm = normalize(worldNorm);
    vec3 lightDir = normalize(lightPos - worldPos);

	vec3 viewDir = normalize(cameraPos - worldPos.xyz);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

	float diff = max(dot(norm, lightDir), 0.0);

	vec4 objectColor = vec4(fragmentColor, 1.0);
	//vec4(0.385,0.647,0.812,1.0);
	
	//I=Ia+Id+Is
	fragColor = ambient + (diff * objectColor * lightColor) + (spec * vec4(1.0, 1.0, 1.0, 1.0));
}