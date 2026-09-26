#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexColor, 0.5);
    //FragColor = vec4(1,1,0, 0.5);
}