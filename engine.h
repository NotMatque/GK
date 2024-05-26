#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <time.h>
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
	Mesh* mesh; 
	Camera* debug_cam; //
	double prev_time;
	double t;
	double max_speed;
	unsigned int randNum;

	// Cube
	Shader* cubeShader;
	VAO* cubeVAO;
	VBO* cubeVBO;
	EBO* cubeEBO;
	Texture* cubeTexture; //
	glm::mat4 baseModel;
	glm::vec3 (*getPos)(float);
	glm::vec3 modelUp;

	// Light
	Shader* ligSourceShader;
	VAO* ligSourceVAO;
	VBO* ligSourceVBO;
	EBO* ligSourceEBO;
	glm::mat4* ligSourceModel;
	glm::vec3* ligSourcePos;
	glm::vec4* ligColor;

	// Board
	Shader* boardShader;
	VAO* boardVAO;
	VBO* boardVBO;
	EBO* boardEBO;
	Texture* boardTexture;
	Texture* boardSpecular;

public:
	Engine();
	bool openGL_init();
	bool mesh_init();
	bool shader_init();
	unsigned int setBaseModels();
	bool setTextures();
	bool camera_init();
	void loop();
	~Engine();
};

#endif