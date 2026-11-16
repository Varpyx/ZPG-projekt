#version 330 core

out vec4 fragColor;

uniform vec4 ambient;
uniform vec3 fragmentColor;

void main(void)
{
	fragColor = ambient * vec4(fragmentColor, 1.0); 
}