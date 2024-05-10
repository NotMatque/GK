#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"


class Camera
{
public:
	glm::vec3 pos;
	glm::vec3 orient = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

	int width, height;

	float speed = 0.1f;
	float sensitivity = 100.f;

	bool frstClick = true;

	Camera(int width_, int height_, glm::vec3 pos_);
	void sendMatrix(Shader& shader, const char* uniform);
	void inputs(GLFWwindow* window);
};

#endif // !CAMERA_H


