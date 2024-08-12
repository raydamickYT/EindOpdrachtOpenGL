#version 330 core

out vec4 FragColor;

in vec4 clipSpace;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

void main()
{
    // Convert clipSpace to NDC
    vec2 ndc = (clipSpace.xy / clipSpace.w) * 0.5 + 0.5; 

    // Calculate reflection and refraction texture coordinates
    vec2 reflectTexCoords = vec2(ndc.x, -ndc.y); // Reflection typically requires flipping the y-coordinate
    vec2 refractTexCoords = ndc;

    // Sample the textures
    vec4 reflectColor = texture(reflectionTexture, reflectTexCoords);
    vec4 refractColor = texture(refractionTexture, refractTexCoords);

    // Mix the colors (adjust the mix factor as needed)
    FragColor = mix(reflectColor, refractColor, 0.5f);

    // Optional: Debugging the reflection by using only one color
    // FragColor = reflectColor; // To see only the reflection texture
}

