#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLuint unit;

	Texture(const char* image, GLenum texType, GLuint slot, GLenum format, GLenum pixelType);
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void bind();
	void unbind();
	void destroy();
};

#endif // !TEXTURE_H


