#version 330 core

uniform vec3 fragmentColor;

in vec3 vertexColor; 
out vec4 FragColor;

void main()
{
    FragColor = vec4(fragmentColor, 1.0);
}