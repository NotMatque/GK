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


// Setting up the vertices:
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

GLfloat vertices[] =
{
	// Bottom side (neg Y)
	-0.5f,  -0.5f, 0.5f,		0.25, 0.0,
	0.5f, -0.5f, 0.5f,			0.5, 0.0,
	0.5f, -0.5f, -0.5f,			0.5, 0.25,
	-0.5f, -0.5f, -0.5f,		0.25, 0.25,
	// Top side (pos Y)
	-0.5f, 0.5f, 0.5f,			0.25, 0.75,
	0.5f, 0.5f, 0.5f,			0.5, 0.75,
	0.5f, 0.5f, -0.5f,			0.5, 0.5,
	-0.5f, 0.5f, -0.5f,			0.25, 0.5,
	// Front side (pos Z)
	-0.5f, -0.5f, 0.5f,			0.25, 1.0,
	0.5f, -0.5f, 0.5f,			0.5, 1.0,
	-0.5f, 0.5f, 0.5f,			0.25, 0.75,
	0.5f, 0.5f, 0.5f,			0.5, 0.75,
	// Back side (neg Z)
	0.5f, -0.5f, -0.5f,			0.5, 0.25,
	-0.5f, -0.5f, -0.5f,		0.25, 0.25,
	0.5f, 0.5f, -0.5f,			0.5, 0.5,
	-0.5f, 0.5f, -0.5f,			0.25, 0.5,
	// Right side (pos X)
	0.5f, -0.5f, 0.5f,			0.5, 1.0,
	0.5f, -0.5f, -0.5f,			0.75, 1.0,
	0.5f, 0.5f, 0.5f,			0.5, 0.75,
	0.5f, 0.5f, -0.5f,			0.75, 0.75,
	// Left side (neg X)
	-0.5f, -0.5f, 0.5f,			0.25, 1.0,
	-0.5f, -0.5f, -0.5f,		0.0, 1.0,
	-0.5f, 0.5f, 0.5f,			0.25, 0.75,
	-0.5f, 0.5f, -0.5f,			0.0, 0.75
};

GLuint indices[]
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

int main()
{
// Init pocedure:
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// Creating a window:
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MGara OpenGL 3D Die", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "ERROR! Failed to create a window!\n";
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

// Creating shader program:
	Shader shaderProg("default.vert", "default.frag");

// Creating Buffers for the object:
	VAO vao1;
	vao1.bind();

	VBO vbo1(vertices, sizeof(vertices));
	EBO ebo1(indices, sizeof(indices));

	vao1.linkAttrib(vbo1, 0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);
	vao1.linkAttrib(vbo1, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));


	vao1.unbind();
	vbo1.unbind();
	ebo1.unbind();


// Model manipulation:
	glEnable(GL_DEPTH_TEST);

// Setting textures:
	Texture brickTex("dietexture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	brickTex.texUnit(shaderProg, "tex0", 0);

// Creating Camera:
	Camera cam1(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

// Main loop:
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProg.activate();
		
		cam1.inputs(window);
		cam1.sendMatrix(shaderProg, "camMatrix");
		brickTex.bind();
		vao1.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(GL_UNSIGNED_INT), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);

		glfwPollEvents();
	}
// Closing procedure:
	vbo1.destroy();
	vao1.destroy();
	ebo1.destroy();
	brickTex.destroy();
	shaderProg.destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}