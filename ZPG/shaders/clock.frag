#version 330 core

uniform vec3 fragmentColor;

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    vec3 color = vertexColor;

    // Black to Grey
    if (vertexColor == vec3(0.0, 0.0, 0.0)) {
        color = vec3(0.6, 0.6, 0.6); 
    } else if (vertexColor == vec3(1.0, 1.0, 0.0)) {
        // Yellow to light blue
        color = vec3(0.5, 0.8, 0.8); 
    } else if (vertexColor == vec3(0.0, 0.0, 1.0) || vertexColor == vec3(0.0, 1.0, 0.0)) {
        // blue or green to black
        color = vec3(0.0, 0.0, 0.0); 
    }

    FragColor = vec4(color, 1.0);
}