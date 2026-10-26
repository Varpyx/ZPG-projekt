#version 330 core

in vec3 vertexColor; 
in vec3 vertexNormal;
in float dist;

out vec4 FragColor;

float attenuation(float d, float c, float l, float q)
{
    // d = distance from the light to the fragment
    // c = constant attenuation factor
    // l = linear attenuation factor
    // q = quadratic attenuation factor
    float att=1.0/ (c + l*d + q*d*d);
    return clamp(att , 0.0 , 1.0);
}

void main()
{
    float att = attenuation(dist, 1.0, 0.19, 0.132);
    float shade = 0.1 + 0.7 * abs(vertexNormal.y);
    FragColor = vec4(shade * vertexColor * att, 1.0);
}