#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aNorm;

out vec2 texCoord;
out vec3 crntPos;
out vec3 Normal;

uniform float scale;
uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
	texCoord = aTex;
	crntPos = vec3(model * vec4(aPos, 1.0f));
	Normal = vec3(transpose(inverse(model)) * vec4(aNorm, 1.0f));

	gl_Position = camMatrix * model * vec4(aPos * scale, 1.0f);
}