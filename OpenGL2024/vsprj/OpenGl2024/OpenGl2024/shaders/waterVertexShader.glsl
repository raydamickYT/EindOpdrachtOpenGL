#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUv; //texture coordinates

out vec4 clipSpace;

uniform mat4 world, view, projection, projectorMatrix; //world == model


void main()
{
	clipSpace = projection * view * world * vec4(aPos, 1.0);
    gl_Position = clipSpace;

	
}