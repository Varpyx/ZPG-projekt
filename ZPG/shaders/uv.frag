#version 330 core

in vec2 vUV;
out vec4 FragColor;

uniform sampler2D textureUnitID;

void main()
{
    FragColor = texture(textureUnitID, vUV);
}
