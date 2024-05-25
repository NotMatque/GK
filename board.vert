#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out vec2 texCoord;
out vec3 crntPos;
out vec3 Normal;

uniform mat4 camMatrix;

void main()
{
	texCoord = aTex;
	crntPos = aPos;
	Normal = aNorm;
	gl_Position = camMatrix * vec4(aPos, 1.0);
}