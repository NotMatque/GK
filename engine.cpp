#include "engine.h"

glm::vec3 setPos1(float _t) { return glm::vec3(_t / 20 * sin(_t), _t / 20 * cos(_t), -0.25f); }
glm::vec3 setPos2(float _t) { return glm::vec3(0.25f, -_t / 20 * sin(_t), _t / 20 * cos(_t)); }
glm::vec3 setPos3(float _t) { return glm::vec3(_t / 20 * sin(_t), 0.25f, _t / 20 * cos(_t)); }
glm::vec3 setPos4(float _t) { return glm::vec3(_t / 20 * cos(_t), -0.25f, _t / 20 * sin(_t)); }
glm::vec3 setPos5(float _t) { return glm::vec3(-0.25f, _t / 20 * sin(_t), _t / 20 * cos(_t)); }
glm::vec3 setPos6(float _t) { return glm::vec3(_t / 20 * sin(_t), -_t / 20 * cos(_t), 0.25f); }

Engine::Engine()
{
	srand(time(NULL));

    bool status = true; // Succesful initialisation
    status &= openGL_init();
    status &= mesh_init();
    status &= shader_init();
    status &= camera_init();

    if (!status)
    {
        std::cout << "ERROR! Engine init failed!\n";
        exit(-1);
    }

    this->t = 10;
    this->max_speed = 0.08;
    this->prev_time = glfwGetTime();
    //this->randNum = (rand() % 6) + 1;
    randNum = 1;

    setBaseModels();
    setTextures();
}

bool Engine::openGL_init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Let the dice roll!", NULL, NULL);

    glfwMakeContextCurrent(this->window);

    gladLoadGL();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    if (this->window == NULL)
    {
        std::cout << "ERROR! Failed to create a window!\n";
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	return true;
}

bool Engine::mesh_init()
{
    this->mesh = new Mesh;
    return mesh != NULL;
}

bool Engine::shader_init()
{
    // Preparing cube shader
    this->cubeShader = new Shader("default.vert", "default.frag");

    this->cubeVAO = new VAO;
    this->cubeVAO->bind();
    cubeVBO = new VBO(mesh->get_vertDefault());
    cubeEBO = new EBO(mesh->get_indiDefault());

    cubeVAO->linkAttrib(*cubeVBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
    cubeVAO->linkAttrib(*cubeVBO, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    cubeVAO->linkAttrib(*cubeVBO, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

    cubeVAO->unbind();
    cubeVBO->unbind();
    cubeEBO->unbind();

    // Preparing light source shader
    this->ligSourceShader = new Shader("LigSource.vert", "LigSource.frag");

    this->ligSourceVAO = new VAO;
    this->ligSourceVAO->bind();
    ligSourceVBO = new VBO(mesh->get_vertLigSource());
    ligSourceEBO = new EBO(mesh->get_indiLigSource());

    ligSourceVAO->linkAttrib(*ligSourceVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);

    ligSourceVAO->unbind();
    ligSourceVBO->unbind();
    ligSourceEBO->unbind();

    // Preparing board shader
    boardShader = new Shader("board.vert", "board.frag");

    boardVAO = new VAO;
    boardVAO->bind();
    boardVBO = new VBO(mesh->get_vertBoard());
    boardEBO = new EBO(mesh->get_indiBoard());

    boardVAO->linkAttrib(*boardVBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
    boardVAO->linkAttrib(*boardVBO, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    boardVAO->linkAttrib(*boardVBO, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

    boardVAO->unbind();
    boardVBO->unbind();
    boardEBO->unbind();

    return true;
}

unsigned int Engine::setBaseModels()
{
    // Light source model data
    ligColor = new glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ligSourcePos = new glm::vec3(1.0f, 2.0f, 1.0f);
    ligSourceModel = new glm::mat4(1.0f);

    *ligSourceModel = glm::translate(*ligSourceModel, *ligSourcePos);
    ligSourceShader->activate();
    glUniform4f(glGetUniformLocation(ligSourceShader->ID, "lightColor"), ligColor->x, ligColor->y, ligColor->z, ligColor->w);
    glUniformMatrix4fv(glGetUniformLocation(ligSourceShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(*ligSourceModel));


    // Cube source model data
    baseModel = glm::mat4(1.0f);
    modelUp = glm::vec3(0.0f, 1.0f, 0.0f);
    switch (randNum)
    {
    case 1:
        baseModel = glm::rotate(baseModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        getPos = &setPos1;
        modelUp = glm::vec3(0.0f, 0.0f, -1.0f);
        break;
    case 2:
        baseModel = glm::rotate(baseModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        getPos = &setPos2;
        modelUp = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    case 3:
        getPos = &setPos3;
        modelUp = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case 4:
        baseModel = glm::rotate(baseModel, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        getPos = &setPos4;
        modelUp = glm::vec3(0.0f, -1.0f, 0.0f);
        break;
    case 5:
        baseModel = glm::rotate(baseModel, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        getPos = &setPos5;
        modelUp = glm::vec3(-1.0f, 0.0f, 0.0f);
        break;
    case 6:
        baseModel = glm::rotate(baseModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        getPos = &setPos6;
        modelUp = glm::vec3(0.0f, 0.0f, 1.0f);
        break;
    default:
        std::cout << "ERROR! Wrong die side chosen!";
        exit(-1);
        break;
    }

    baseModel = glm::translate(baseModel, getPos(t));

    cubeShader->activate();
    glUniform1f(glGetUniformLocation(cubeShader->ID, "scale"), 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(baseModel));
    glUniform4f(glGetUniformLocation(cubeShader->ID, "lightColor"), ligColor->x, ligColor->y, ligColor->z, ligColor->w);
    glUniform3f(glGetUniformLocation(cubeShader->ID, "lightPos"), ligSourcePos->x, ligSourcePos->y, ligSourcePos->z);

    boardShader->activate();
    glUniform4f(glGetUniformLocation(boardShader->ID, "lightColor"), ligColor->x, ligColor->y, ligColor->z, ligColor->w);
    glUniform3f(glGetUniformLocation(boardShader->ID, "lightPos"), ligSourcePos->x, ligSourcePos->y, ligSourcePos->z);

    return randNum;
}

bool Engine::setTextures()
{
    cubeTexture = new Texture("img/dietexture.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    cubeTexture->texUnit(*cubeShader, "texCube", 0);
    boardTexture = new Texture("img/planks.png", GL_TEXTURE_2D, 1, GL_RGBA, GL_UNSIGNED_BYTE);
    boardTexture->texUnit(*boardShader, "texPlanks", 1);
    boardSpecular = new Texture("img/planksSpec.png", GL_TEXTURE_2D, 2, GL_RED, GL_UNSIGNED_BYTE);
    boardSpecular->texUnit(*boardShader, "texSpec", 2);

    return (cubeTexture != NULL) && (boardTexture != NULL) && (boardSpecular != NULL);
}

bool Engine::camera_init()
{
    debug_cam = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(1.0f, 2.15f, 2.0f), glm::vec3(-1.1f, -2.0f, -2.0f));
    return debug_cam != NULL;
}

void Engine::loop()
{
    glm::mat4 defObjModel = baseModel; // Setting default matrix as base matrix
    glm::vec3 defObjPos = getPos(t); // Offset vector from origin (0.0f, 0.0f, 0.0f)
    glm::vec3 up = modelUp;
    defObjModel = glm::translate(defObjModel, defObjPos);

    unsigned int fpsCounter = 0;
    while (!glfwWindowShouldClose(window))
    {
        fpsCounter++;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        debug_cam->getInputs(window);

        // Timer
        double crntTime = glfwGetTime();
        if ((crntTime - prev_time >= 1 / 60) and (t >= 0))
        {
            t -= max_speed * (-pow(((10 - t) / 10), 5) + 1);

            defObjModel = baseModel;
            defObjPos = getPos(t);

            defObjModel = glm::translate(defObjModel, defObjPos);
            defObjModel = glm::rotate(defObjModel, (float)glm::radians(-200 * t), up);

            std::string FPS = std::to_string((1.0 / (crntTime - prev_time)) * fpsCounter);
            std::string newTitle = "Let the dice roll! | " + FPS;
            glfwSetWindowTitle(window, newTitle.c_str());
            fpsCounter = 0;

            prev_time = crntTime;
        }

        cubeShader->activate();
        glUniform3f(glGetUniformLocation(cubeShader->ID, "camPos"), debug_cam->pos.x, debug_cam->pos.y, debug_cam->pos.z);
        glUniformMatrix4fv(glGetUniformLocation(cubeShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(defObjModel));
        debug_cam->sendMatrix(*cubeShader, "camMatrix");
        cubeTexture->bind();
        cubeVAO->bind();
        glDrawElements(GL_TRIANGLES, mesh->get_indiDefault().size(), GL_UNSIGNED_INT, 0);

        ligSourceShader->activate();
        ligSourceVAO->bind();
        debug_cam->sendMatrix(*ligSourceShader, "camMatrix");
        glDrawElements(GL_TRIANGLES, mesh->get_indiLigSource().size(), GL_UNSIGNED_INT, 0);

        boardShader->activate();
        boardVAO->bind();
        boardTexture->bind();
        boardSpecular->bind();
        debug_cam->sendMatrix(*boardShader, "camMatrix");
        glDrawElements(GL_TRIANGLES, mesh->get_indiBoard().size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

Engine::~Engine()
{
    cubeVBO->destroy();
    cubeVAO->destroy();
    cubeEBO->destroy();
    cubeShader->destroy();

    ligSourceVBO->destroy();
    ligSourceVAO->destroy();
    ligSourceEBO->destroy();
    ligSourceShader->destroy();

    boardVBO->destroy();
    boardVAO->destroy();
    boardEBO->destroy();
    boardShader->destroy();

    cubeTexture->destroy();
    boardTexture->destroy();
    boardSpecular->destroy();

    glfwDestroyWindow(window);
    glfwTerminate();

}
