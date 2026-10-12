#version 330 core

uniform vec3 fragmentColor;

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    vec3 color = vertexColor;
    if (color == vec3(0.0, 0.0, 0.0)) {
        color = vec3(1.0, 1.0, 0.0); // Černá -> Žlutá
    } 
    else if (color == vec3(0.0, 1.0, 1.0)) {
        color = vec3(1.0, 0.0, 0.0); // Zelenomodrá (Cyan) -> Červená
    }
    else if (color == vec3(0.0, 0.0, 1.0)) {
        color = vec3(0.0, 0.0, 0.0); // Modrá -> Černá
    }
    else if (color == vec3(1.0, 1.0, 0.0)) {
        color = vec3(0.0, 0.0, 0.0); // Původní Žlutá -> Černá
    }

    FragColor = vec4(color, 1.0);
}