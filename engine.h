#ifndef ENGINE_H
#define ENGINE_H

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

#include "Camera.h"
#include "Texture.h"

#include "mesh_class.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

class Engine{
	GLFWwindow *window;

public:
	Engine()=default;
	int engine_init();
	void engine_loop(Camera cam,Texture& texDef, Mesh test_mesh, Shader shaderDefault, Shader shaderLig, VAO vaoDef);
	void engine_terminate(Texture& texDef);
};

#endif