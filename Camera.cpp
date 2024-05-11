#include "Camera.h"

Camera::Camera(int width_, int height_, glm::vec3 pos_)
{
	this->width = width_;
	this->height = height_;
	this->pos = pos_;
}

void Camera::sendMatrix(Shader& shader, const char* uniform)
{
	glm::mat4 view(1.0f);
	glm::mat4 proj(1.0f);

	float FOVdeg = 45.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	view = glm::lookAt(this->pos, this->pos + this->orient, this->up);
	proj = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::getInputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos += speed * orient;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos += speed * -orient;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos += speed * -glm::normalize(glm::cross(orient, up));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos += speed * glm::normalize(glm::cross(orient, up));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		pos += speed * up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		pos += speed * -up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		speed = 0.04;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		speed = 0.01;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (frstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			frstClick = false;
		}

		double mouseX, mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		// Calculates upcoming vertical change in the orient
		glm::vec3 newOrientation = glm::rotate(orient, glm::radians(-rotX), glm::normalize(glm::cross(orient, up)));

		// Decides whether or not the next vertical orient is legal or not
		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orient = newOrientation;
		}

		// Rotates the orient left and right
		orient = glm::rotate(orient, glm::radians(-rotY), up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		frstClick = true;
	}
}
