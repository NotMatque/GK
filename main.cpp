#include <iostream>
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

#include "engine.h"
#include "shader_buffor_methods.h"
#include"model.h"
#include "mesh_class.h"



int main() {

    GLFWwindow* window = engine_init();

    if (window == NULL) {
        std::cout << "ERROR! Failed to create a window!\n";
        return -1;
    }

    //Create mesh
    Mesh test_mesh("./obj_files/untitled.obj");

    // Creating shader and buffers
    Shader shaderDefault("default.vert", "default.frag");
    Shader shaderLig("ligSource.vert", "ligSource.frag");

    VAO vaoDef;
    VBO vboDef(test_mesh.get_vertDefault());
    EBO eboDef(test_mesh.get_indiDefault());

    VAO vaoLig;
    VBO vboLig(test_mesh.get_vertLigSource());
    EBO eboLig(test_mesh.get_indiLigSource());

    //Shader init
    shader_buffor_init(vaoDef, vboDef, eboDef, vaoLig, vboLig, eboLig, test_mesh);

    // Model manipulation:
    glEnable(GL_DEPTH_TEST);

    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 ligPos(1.0f, 2.0f, 1.0f);
    glm::mat4 ligModel(1.0f);

    model_manip(lightColor, ligPos, ligModel, shaderDefault, shaderLig);

    // Setting textures:
    Texture texDef("img/dietexture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texDef.texUnit(shaderDefault, "tex0", 0);

    // Creating Camera:
    Camera debugCamera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.5f, 2.0f));
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); int time = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        debugCamera.getInputs(window);

        shaderDefault.activate();
        glUniform3f(glGetUniformLocation(shaderDefault.ID, "camPos"), debugCamera.pos.x, debugCamera.pos.y, debugCamera.pos.z);
        debugCamera.sendMatrix(shaderDefault, "camMatrix");
        texDef.bind();
        vaoDef.bind();
        glDrawElements(GL_TRIANGLES, test_mesh.get_indiDefault().size(), GL_UNSIGNED_INT, 0);

        shaderLig.activate();
        debugCamera.sendMatrix(shaderLig, "camMatrix");

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    // Closing procedure:

    engine_terminate(window, texDef);
    shader_buffor_terminate(vaoDef, vboDef, eboDef, vaoLig, vboLig, eboLig, shaderDefault, shaderLig);
    return 0;
}