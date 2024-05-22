#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include<vector>

void load_obj(std::string inputfile, std::vector<GLfloat>& verticies, std::vector<GLuint>& indicies);

#endif
