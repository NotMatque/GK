#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"


class Mesh {
	std::vector<GLfloat> vert;
	std::vector<GLuint> indi;
	std::vector<GLfloat> vertLigSource = {
		-0.1f, -0.1f, 0.1f,		// 0	  7--------6
		0.1f, -0.1f, 0.1f,		// 1	 /|       /|
		0.1f, -0.1f, -0.1f,		// 2	4--------5 |
		-0.1f, -0.1f, -0.1f,	// 3	| |      | |
		-0.1f, 0.1f, 0.1f,		// 4	| 3------|-2
		0.1f, 0.1f, 0.1f,		// 5	|/       |/
		0.1f, 0.1f, -0.1f,		// 6	0--------1
		-0.1f, 0.1f, -0.1f		// 7
	};
	std::vector<GLuint> indiLigSource = {
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
	std::vector<GLfloat> vertBoard = {
		-6.0f,  0.0f, 6.0f,		0.0, 0.0,		0.0, 1.0, 0.0,
		6.0f, 0.0f, 6.0f,		5.0, 0.0,		0.0, 1.0, 0.0,
		6.0f, 0.0f, -6.0f,		5.0, 5.0,		0.0, 1.0, 0.0,
		-6.0f, 0.0f, -6.0f,		0.0, 5.0,		0.0, 1.0, 0.0,
	};
	std::vector<GLuint> indiBoard = {
		0, 1, 2,
		0, 2, 3,
	};

public:
	Mesh();
	Mesh(std::string obj_path);

	std::vector <GLfloat> get_vertDefault();
	std::vector <GLuint> get_indiDefault();
	std::vector <GLfloat> get_vertLigSource();
	std::vector <GLuint> get_indiLigSource();
	std::vector <GLfloat> get_vertBoard();
	std::vector <GLuint> get_indiBoard();
};

#endif
