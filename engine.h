#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
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
#include "mesh_class.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

class Engine
{
private:
	// Key engine components
	GLFWwindow *window;
	Mesh* test_mesh;
	Camera* debug_cam;
	double prev_time;
	float t;
	float max_speed;

	// Cube
	Shader* cubeShader;
	VAO* cubeVAO;
	VBO* cubeVBO;
	EBO* cubeEBO;
	Texture* cubeTexture;

	// Light
	Shader* ligSourceShader;
	VAO* ligSourceVAO;
	VBO* ligSourceVBO;
	EBO* ligSourceEBO;

	// Board
	Shader* boardShader;
	VAO* boardVAO;
	VBO* boardVBO;
	EBO* boardEBO;
	Texture* boardTexture;

public:
	Engine();
	bool init();
	bool glfw_init();
	bool buffor_init();
	bool model_init();
	bool camera_init();
	bool tex_init();

	void engine_loop(Camera cam,Texture& texDef, Mesh test_mesh, Shader shaderDefault, Shader shaderLig, VAO vaoDef);
	void engine_terminate(Texture& texDef);
};

#endif