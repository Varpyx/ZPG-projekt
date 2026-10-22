#version 330 core

in vec3 worldPos;
in vec3 worldNorm;

out vec4 fragColor;

uniform vec4 lightColor; 
uniform vec4 ambient;
uniform vec3 fragmentColor;

void main(void)
{
	vec4 objectColor = vec4(fragmentColor, 1.0);
	
	//result = ambient strength * color 
	vec4 result_amb = ambient * lightColor;

	fragColor = result_amb * objectColor; 
}