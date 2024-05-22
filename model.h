#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"

void model_manip(glm::vec4& lightColor, glm::vec3& ligPos, glm::mat4& ligModel, Shader& shaderDefault, Shader& shaderLig);

#endif
