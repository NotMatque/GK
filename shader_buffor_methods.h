#ifndef SHADER_BUFFOR_METHODS_H
#define SHADER_BUFFOR_METHODS_H
#include <iostream>
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

#include "mesh_class.h"

void shader_buffor_init(VAO& vaoDef, VBO& vboDef, EBO& eboDef, VAO vaoLig, VBO vboLig, EBO eboLig, Mesh mesh);

void shader_buffor_terminate(VAO& vaoDef, VBO& vboDef, EBO& eboDef,
							 VAO vaoLig, VBO vboLig, EBO eboLig,
							 Shader& shaderDefault, Shader& shaderLig);

#endif
