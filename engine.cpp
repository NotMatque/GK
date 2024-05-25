#include "engine.h"

Engine::Engine()
{
	if (!init())
	{
		std::cout << "ERROR! Engine failed!\n";
		exit(-1);
	}
		
}

bool Engine::init()
{
	bool status = true;

	status &= glfw_init();
	status &= model_init();
	status &= buffor_init();
	status &= camera_init();
	status &= tex_init();

	return status;
}

bool Engine::glfw_init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Let the dice roll!", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	if (window == NULL)
	{
		std::cout << "ERROR! Failed to create a window!\n";
		return false;
	}

	glEnable(GL_DEPTH_TEST);

	return true;
}

bool Engine::model_init()
{
	//test_mesh = new Mesh("./obj_files/untitled.obj");
	test_mesh = new Mesh;

	return false;
}

bool Engine::buffor_init()
{
	cubeShader = new Shader("default.vert", "default.frag");
	cubeVAO = new VAO; cubeVAO->bind();
	cubeVBO = new VBO(test_mesh->get_vertDefault());
	cubeEBO = new EBO(test_mesh->get_indiDefault());

	cubeVAO->linkAttrib(*cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
	cubeVAO->linkAttrib(*cubeVBO, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	cubeVAO->linkAttrib(*cubeVBO, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	
	cubeVAO->unbind();
	cubeVBO->unbind();
	cubeEBO->unbind();

	return true;
}

bool Engine::camera_init()
{
	debug_cam = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 0.5f, 2.0f));
	return debug_cam != NULL;
}

bool Engine::tex_init()
{
	return false;
}

void Engine::engine_loop(Camera cam, Texture& texDef, Mesh test_mesh, Shader shaderDefault, Shader shaderLig, VAO vaoDef)
{
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

void Engine::engine_terminate(Texture& texDef)
{
	texDef.destroy();	
	glfwDestroyWindow(window);
	glfwTerminate();
}