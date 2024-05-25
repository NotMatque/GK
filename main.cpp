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

    Engine engine;

    if (engine.engine_init() == -1) {
        std::cout << "ERROR! Failed to create a window!\n";
        return -1;
    }

    //Create mesh
    Mesh test_mesh("./obj_files/klocekszescioscienny.obj");

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
    Texture texDef("img/d6.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    texDef.texUnit(shaderDefault, "tex0", 0);

    // Creating Camera:
    Camera cam = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.5f, 2.0f));
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f); int time = 0;
    
    engine.engine_loop(cam, texDef, test_mesh, shaderDefault, shaderLig, vaoDef);

    // Closing procedure:

    shader_buffor_terminate(vaoDef, vboDef, eboDef, vaoLig, vboLig, eboLig, shaderDefault, shaderLig);
    engine.engine_terminate(texDef);
    return 0;
}