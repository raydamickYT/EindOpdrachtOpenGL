#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform vec4 plane;
out vec2 TexCoords;
out float clipValue;

void main()
{
    vec4 pos = vec4(aPos, 0.0, 1.0);
   // vec4 plane = vec4(0, -1, 0, -600); // Vlak gedefinieerd in 4D ruimte;
    clipValue = dot(pos, plane);

    gl_ClipDistance[0] = dot(pos, plane);
    TexCoords = aTexCoords;
    gl_Position = pos;
}
