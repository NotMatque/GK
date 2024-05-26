#include <iostream>

#include "engine.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

glm::vec3 setPosition1(float _t) { return glm::vec3(_t / 20 * sin(_t), _t / 20 * cos(_t), -0.25f); }
glm::vec3 setPosition2(float _t) { return glm::vec3(0.25f, -_t / 20 * sin(_t), _t / 20 * cos(_t)); }
glm::vec3 setPosition3(float _t) { return glm::vec3(_t / 20 * sin(_t), 0.25f, _t / 20 * cos(_t)); }
glm::vec3 setPosition4(float _t) { return glm::vec3(_t / 20 * cos(_t), -0.25f, _t / 20 * sin(_t)); }
glm::vec3 setPosition5(float _t) { return glm::vec3(-0.25f, _t / 20 * sin(_t), _t / 20 * cos(_t)); }
glm::vec3 setPosition6(float _t) { return glm::vec3(_t / 20 * sin(_t), -_t / 20 * cos(_t), 0.25f); }

int engineV()
{
    Engine scene1;
    scene1.loop();

    return 0;
}

int pureV() {
    srand(time(NULL));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Let the dice roll!", NULL, NULL);

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    if (window == NULL)
    {
        std::cout << "ERROR! Failed to create a window!\n";
        exit(-1);
    }

    //Create mesh - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    //Mesh test_mesh("./obj_files/klocekszescioscienny.obj");
    Mesh test_mesh;

    // Creating shader and buffers
    Shader shaderDefault("default.vert", "default.frag");
    Shader shaderLig("ligSource.vert", "ligSource.frag");
    Shader shaderBoard("board.vert", "board.frag");

    //Shader init
    VAO vaoDef; vaoDef.bind();
    VBO vboDef(test_mesh.get_vertDefault()); // VBO of default object
    EBO eboDef(test_mesh.get_indiDefault()); // EBO of default object

    vaoDef.linkAttrib(vboDef, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
    vaoDef.linkAttrib(vboDef, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    vaoDef.linkAttrib(vboDef, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

    vaoDef.unbind();
    vboDef.unbind();
    eboDef.unbind();

    VAO vaoLig; vaoLig.bind();
    VBO vboLig(test_mesh.get_vertLigSource());
    EBO eboLig(test_mesh.get_indiLigSource());

    vaoLig.linkAttrib(vboLig, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);

    vaoLig.unbind();
    vboLig.unbind();
    eboLig.unbind();

    VAO vaoBoard; vaoBoard.bind();
    VBO vboBoard(test_mesh.get_vertBoard());
    EBO eboBoard(test_mesh.get_indiBoard());

    vaoBoard.linkAttrib(vboBoard, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
    vaoBoard.linkAttrib(vboBoard, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    vaoBoard.linkAttrib(vboBoard, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

    vaoBoard.unbind();
    vboBoard.unbind();
    eboBoard.unbind();

    // Model manipulation:
    glEnable(GL_DEPTH_TEST);

    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 ligPos(1.0f, 2.0f, 1.0f);
    glm::mat4 ligModel(1.0f);

    ligModel = glm::translate(ligModel, ligPos);
    shaderLig.activate();
    glUniform4f(glGetUniformLocation(shaderLig.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniformMatrix4fv(glGetUniformLocation(shaderLig.ID, "model"), 1, GL_FALSE, glm::value_ptr(ligModel));

    // Time passing logic:
    float t = 10; float speed = 0.08;
    double prevTime = glfwGetTime();

    // Settign base model matrix
    glm::mat4 defBaseModel(1.0f);
    glm::vec3 (*getVector)(float) = &setPosition3;
    glm::vec3 newUp;

    int randNum = 1;

    switch (randNum)
    {
    case 1:
        defBaseModel = glm::rotate(defBaseModel, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        getVector = &setPosition1;
        newUp = glm::vec3(0.0f, 0.0f, -1.0f);
        break;
    case 2:
        defBaseModel = glm::rotate(defBaseModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        getVector = &setPosition2;
        newUp = glm::vec3(1.0f, 0.0f, 0.0f);
        break;
    case 3:
        getVector = &setPosition3;
        newUp = glm::vec3(0.0f, 1.0f, 0.0f);
        break;
    case 4:
        defBaseModel = glm::rotate(defBaseModel, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        getVector = &setPosition4;
        newUp = glm::vec3(0.0f, -1.0f, 0.0f);
        break;
    case 5:
        defBaseModel = glm::rotate(defBaseModel, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        getVector = &setPosition5;
        newUp = glm::vec3(-1.0f, 0.0f, 0.0f);
        break;
    case 6:
        defBaseModel = glm::rotate(defBaseModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        getVector = &setPosition6;
        newUp = glm::vec3(0.0f, 0.0f, 1.0f);
        break;
    default:
        std::cout << "ERROR! Wrong die side chosen!";
        exit(-1);
        break;
    }


    glm::mat4 defObjModel = defBaseModel; // Setting default matrix as base matrix
    glm::vec3 defObjPos = getVector(t); // Offset vector from origin (0.0f, 0.0f, 0.0f)
    glm::vec3 up = newUp;
    defObjModel = glm::translate(defObjModel, defObjPos);

    shaderDefault.activate();
    glUniform1f(glGetUniformLocation(shaderDefault.ID, "scale"), 0.5f);
    glUniformMatrix4fv(glGetUniformLocation(shaderDefault.ID, "model"), 1, GL_FALSE, glm::value_ptr(defObjModel));
    glUniform4f(glGetUniformLocation(shaderDefault.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderDefault.ID, "lightPos"), ligPos.x, ligPos.y, ligPos.z);

    shaderBoard.activate();
    glUniform4f(glGetUniformLocation(shaderBoard.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderBoard.ID, "lightPos"), ligPos.x, ligPos.y, ligPos.z);

    // Setting textures:
    Texture texDef("img/dietexture.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    texDef.texUnit(shaderDefault, "texCube", 0);
    Texture texPlanks("img/planks.png", GL_TEXTURE_2D, 1, GL_RGBA, GL_UNSIGNED_BYTE);
    texPlanks.texUnit(shaderBoard, "texPlanks", 1);
    Texture texPlanksSpec("img/planksSpec.png", GL_TEXTURE_2D, 2, GL_RED, GL_UNSIGNED_BYTE);
    texPlanksSpec.texUnit(shaderBoard, "texSpec", 2);

    // Creating Camera:
    //Camera cam = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(1.0f, 2.0f, 2.0f), glm::vec3(-1.1f, -1.9f, -2.0f));
    Camera cam = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(1.0f, 2.15f, 2.0f), glm::vec3(-1.1f, -2.0f, -2.0f));
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); int time = 0;
    

    //Main while loop
    unsigned int fpsCounter = 0;
    while (!glfwWindowShouldClose(window))
    {
        fpsCounter++;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cam.getInputs(window);

        // Timer
        double crntTime = glfwGetTime();
        if ((crntTime - prevTime >= 1 / 60) and (t >= 0))
        {
            t -= speed * (-pow(((10 - t) / 10), 5) + 1);

            defObjModel = defBaseModel;
            defObjPos = getVector(t);

            defObjModel = glm::translate(defObjModel, defObjPos);
            defObjModel = glm::rotate(defObjModel, glm::radians(-200 * t), up);

            std::string FPS = std::to_string((1.0 / (crntTime - prevTime)) * fpsCounter);
            std::string newTitle = "Let the dice roll! | " + FPS;
            glfwSetWindowTitle(window, newTitle.c_str());
            fpsCounter = 0;

            prevTime = crntTime;
        }

        shaderDefault.activate();
        glUniform3f(glGetUniformLocation(shaderDefault.ID, "camPos"), cam.pos.x, cam.pos.y, cam.pos.z);
        glUniformMatrix4fv(glGetUniformLocation(shaderDefault.ID, "model"), 1, GL_FALSE, glm::value_ptr(defObjModel));
        cam.sendMatrix(shaderDefault, "camMatrix");
        texDef.bind();
        vaoDef.bind();
        glDrawElements(GL_TRIANGLES, test_mesh.get_indiDefault().size(), GL_UNSIGNED_INT, 0);

        shaderLig.activate();
        vaoLig.bind();
        cam.sendMatrix(shaderLig, "camMatrix");
        glDrawElements(GL_TRIANGLES, test_mesh.get_indiLigSource().size(), GL_UNSIGNED_INT, 0);

        shaderBoard.activate();
        vaoBoard.bind();
        texPlanks.bind();
        texPlanksSpec.bind();
        cam.sendMatrix(shaderBoard, "camMatrix");
        glDrawElements(GL_TRIANGLES, test_mesh.get_indiBoard().size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    // Closing procedure:
    vboDef.destroy();
    vaoDef.destroy();
    eboDef.destroy();
    shaderDefault.destroy();

    vboLig.destroy();
    vaoLig.destroy();
    eboLig.destroy();
    shaderLig.destroy();

    vboBoard.destroy();
    vaoBoard.destroy();
    eboBoard.destroy();
    shaderBoard.destroy();

    texDef.destroy();
    texPlanks.destroy();
    texPlanksSpec.destroy();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

int main()
{
    engineV();
    pureV();
    return 0;
}