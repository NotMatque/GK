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
	std::vector<GLfloat> vertDefault;
	std::vector<GLuint> indiDefault;
	std::vector<GLfloat> vertLigSource;
	std::vector<GLuint> indiLigSource;


public:
	Mesh();
	void load_obj(std::string inputfile, std::vector<GLfloat>& verticies, std::vector<GLuint>& indicies);
	Mesh(std::string obj_path);

	std::vector <GLfloat> get_vertDefault();
	std::vector <GLuint> get_indiDefault();
	std::vector <GLfloat> get_vertLigSource();
	std::vector <GLuint> get_indiLigSource();
};

#endif
