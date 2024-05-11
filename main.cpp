#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

// Definitions:
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

// Setting up the vertDefault:
/*
//   Coordinates
-1.0f, -1.0f, 1.0f,		// 0	  7--------6
1.0f, -1.0f, 1.0f,		// 1	 /|       /|
1.0f, -1.0f, -1.0f,		// 2	4--------5 |
-1.0f, -1.0f, -1.0f,	// 3	| |      | |
-1.0f, 1.0f, 1.0f,		// 4	| 3------|-2
1.0f, 1.0f, 1.0f,		// 5	|/       |/
1.0f, 1.0f, -1.0f,		// 6	0--------1
-1.0f, 1.0f, -1.0f		// 7
*/

GLfloat vertDefault[] =
{
	// Bottom side (neg Y)
	-0.5f,  -0.5f, 0.5f,		0.25, 0.0,		0.0, -1.0, 0.0,
	0.5f, -0.5f, 0.5f,			0.5, 0.0,		0.0, -1.0, 0.0,
	0.5f, -0.5f, -0.5f,			0.5, 0.25,		0.0, -1.0, 0.0,
	-0.5f, -0.5f, -0.5f,		0.25, 0.25,		0.0, -1.0, 0.0,
	// Top side (pos Y)
	-0.5f, 0.5f, 0.5f,			0.25, 0.75,		0.0, 1.0, 0.0,
	0.5f, 0.5f, 0.5f,			0.5, 0.75,		0.0, 1.0, 0.0,
	0.5f, 0.5f, -0.5f,			0.5, 0.5,		0.0, 1.0, 0.0,
	-0.5f, 0.5f, -0.5f,			0.25, 0.5,		0.0, 1.0, 0.0,
	// Front side (pos Z)
	-0.5f, -0.5f, 0.5f,			0.25, 1.0,		0.0, 0.0, 1.0,
	0.5f, -0.5f, 0.5f,			0.5, 1.0,		0.0, 0.0, 1.0,
	-0.5f, 0.5f, 0.5f,			0.25, 0.75,		0.0, 0.0, 1.0,
	0.5f, 0.5f, 0.5f,			0.5, 0.75,		0.0, 0.0, 1.0,
	// Back side (neg Z)
	0.5f, -0.5f, -0.5f,			0.5, 0.25,		0.0, 0.0, -1.0,
	-0.5f, -0.5f, -0.5f,		0.25, 0.25,		0.0, 0.0, -1.0,
	0.5f, 0.5f, -0.5f,			0.5, 0.5,		0.0, 0.0, -1.0,
	-0.5f, 0.5f, -0.5f,			0.25, 0.5,		0.0, 0.0, -1.0,
	// Right side (pos X)
	0.5f, -0.5f, 0.5f,			0.5, 1.0,		1.0, 0.0, 0.0,
	0.5f, -0.5f, -0.5f,			0.75, 1.0,		1.0, 0.0, 0.0,
	0.5f, 0.5f, 0.5f,			0.5, 0.75,		1.0, 0.0, 0.0,
	0.5f, 0.5f, -0.5f,			0.75, 0.75,		1.0, 0.0, 0.0,
	// Left side (neg X)
	-0.5f, -0.5f, 0.5f,			0.25, 1.0,		-1.0, 0.0, 0.0,
	-0.5f, -0.5f, -0.5f,		0.0, 1.0,		-1.0, 0.0, 0.0,
	-0.5f, 0.5f, 0.5f,			0.25, 0.75,		-1.0, 0.0, 0.0,
	-0.5f, 0.5f, -0.5f,			0.0, 0.75,		-1.0, 0.0, 0.0,
};

GLuint indiDefault[]
{
	// Bottom side
	0, 1, 2,
	0, 2, 3,
	// Top side
	4, 5, 6,
	4, 6, 7,
	// Front side
	8, 9, 10,
	9, 10, 11,
	// Back side
	12, 13, 14,
	13, 14, 15,
	// Right side
	16, 17, 18,
	17, 18, 19,
	// Left side
	20, 21, 22,
	21, 22, 23
};

GLfloat vertLigSource[] =
{
	-0.1f, -0.1f, 0.1f,		// 0	  7--------6
	0.1f, -0.1f, 0.1f,		// 1	 /|       /|
	0.1f, -0.1f, -0.1f,		// 2	4--------5 |
	-0.1f, -0.1f, -0.1f,	// 3	| |      | |
	-0.1f, 0.1f, 0.1f,		// 4	| 3------|-2
	0.1f, 0.1f, 0.1f,		// 5	|/       |/
	0.1f, 0.1f, -0.1f,		// 6	0--------1
	-0.1f, 0.1f, -0.1f		// 7
};

GLuint indiLigSource[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

GLfloat vertBoard[] =
{
	-2.0, 0.0, 2.0,
	2.0, 0.0, 2.0,
	2.0, 0.0, -2.0,
	-2.0, 0.0, -2.0
};

GLuint indiBoard[] =
{
	0, 1, 2,
	0, 2, 3
};

int main()
{
// Init pocedure:
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// Creating a window:
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MGara OpenGL 3D Die with light", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "ERROR! Failed to create a window!\n";
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

// Creating shader and buffers for the default object:
	Shader shaderDefault("default.vert", "default.frag"); // Shader for the default object

	VAO vaoDef; // VAO of default object
	vaoDef.bind();
	VBO vboDef(vertDefault, sizeof(vertDefault)); // VBO of default object
	EBO eboDef(indiDefault, sizeof(indiDefault)); // EBO of default object

	vaoDef.linkAttrib(vboDef, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
	vaoDef.linkAttrib(vboDef, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	vaoDef.linkAttrib(vboDef, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	vaoDef.unbind();
	vboDef.unbind();
	eboDef.unbind();

// Creating shader and buffers for the lightSource:
	Shader shaderLig("ligSource.vert", "ligSource.frag");
	VAO vaoLig; vaoLig.bind();
	VBO vboLig(vertLigSource, sizeof(vertLigSource));
	EBO eboLig(indiLigSource, sizeof(indiLigSource));
	vaoLig.linkAttrib(vboLig, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
	vaoLig.unbind();
	vboLig.unbind();
	eboLig.unbind();

// Model manipulation:
	glEnable(GL_DEPTH_TEST);

	glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 ligPos(1.0f, 2.0f, 1.0f);
	glm::mat4 ligModel(1.0f);
	ligModel = glm::translate(ligModel, ligPos);
	shaderLig.activate();
	glUniform4f(glGetUniformLocation(shaderLig.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniformMatrix4fv(glGetUniformLocation(shaderLig.ID, "model"), 1, GL_FALSE, glm::value_ptr(ligModel));

	glm::vec3 defObjPos(0.0f, 0.5f, 0.0f);
	glm::mat4 defObjModel(1.0f);
	defObjModel = glm::translate(defObjModel, defObjPos);
	shaderDefault.activate();
	glUniform1f(glGetUniformLocation(shaderDefault.ID, "scale"), 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderDefault.ID, "model"), 1, GL_FALSE, glm::value_ptr(defObjModel));
	glUniform4f(glGetUniformLocation(shaderDefault.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderDefault.ID, "lightPos"), ligPos.x, ligPos.y, ligPos.z);


// Setting textures:
	Texture texDef("dietexture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texDef.texUnit(shaderDefault, "tex0", 0);

// Creating Camera:
	Camera debugCamera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.5f, 2.0f));

// Main loop:
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); int time = 0;
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		debugCamera.getInputs(window);

		shaderDefault.activate();
		glUniform3f(glGetUniformLocation(shaderDefault.ID, "camPos"), debugCamera.pos.x, debugCamera.pos.y, debugCamera.pos.z);
		debugCamera.sendMatrix(shaderDefault, "camMatrix");
		texDef.bind();
		vaoDef.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indiDefault) / sizeof(GL_UNSIGNED_INT), GL_UNSIGNED_INT, 0);

		shaderLig.activate();
		debugCamera.sendMatrix(shaderLig, "camMatrix");
		
		vaoLig.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indiLigSource) / sizeof(GL_UNSIGNED_INT), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
// Closing procedure:
	vboDef.destroy();
	vaoDef.destroy();
	eboDef.destroy();
	texDef.destroy();
	shaderDefault.destroy();
	vboLig.destroy();
	vaoLig.destroy();
	eboLig.destroy();
	shaderLig.destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}