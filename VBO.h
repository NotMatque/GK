#ifndef VBO_H
#define VBO_H

#include<glad/glad.h>
#include <vector>

class VBO
{
public:
	GLuint ID;
	VBO(std::vector<GLfloat> vertices);
	void bind();
	void unbind();
	void destroy();
};

#endif // !VBO_H

