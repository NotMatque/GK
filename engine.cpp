#include "engine.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800



int Engine::engine_init(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MGara OpenGL 3D Die with light", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (window == NULL) { return -1; }

	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	return 0;
}


void Engine::engine_loop(Camera cam, Texture& texDef, Mesh test_mesh, Shader shaderDefault, Shader shaderLig, VAO vaoDef) {
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam.getInputs(window);

		shaderDefault.activate();
		glUniform3f(glGetUniformLocation(shaderDefault.ID, "camPos"), cam.pos.x, cam.pos.y, cam.pos.z);
		cam.sendMatrix(shaderDefault, "camMatrix");
		texDef.bind();
		vaoDef.bind();
		glDrawElements(GL_TRIANGLES, test_mesh.get_indiDefault().size(), GL_UNSIGNED_INT, 0);

		shaderLig.activate();
		cam.sendMatrix(shaderLig, "camMatrix");

		glfwSwapBuffers(window);

		glfwPollEvents();
	}
}

void Engine::engine_terminate(Texture& texDef) {
	texDef.destroy();	
	glfwDestroyWindow(window);
	glfwTerminate();
}