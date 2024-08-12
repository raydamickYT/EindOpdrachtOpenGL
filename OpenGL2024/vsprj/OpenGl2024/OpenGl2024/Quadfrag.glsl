#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in float clipValue;

uniform sampler2D screenTexture;

void main()
{
    if (clipValue < 300.0) 
    {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Rood als het punt geclipt zou worden
    } else 
    {
        FragColor = vec4(0.0, 1.0, 0.0, 1.0); // Groen als het punt niet geclipt wordt
    }
    FragColor = texture(screenTexture, vec2(TexCoords.x, -TexCoords.y));
}
