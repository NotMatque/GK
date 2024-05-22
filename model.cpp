#include"model.h"

void model_manip(glm::vec4& lightColor, glm::vec3& ligPos, glm::mat4& ligModel, Shader& shaderDefault, Shader& shaderLig) {
	ligModel = glm::translate(ligModel, ligPos);
	shaderLig.activate();
	glUniform4f(glGetUniformLocation(shaderLig.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniformMatrix4fv(glGetUniformLocation(shaderLig.ID, "model"), 1, GL_FALSE, glm::value_ptr(ligModel));

	glm::vec3 defObjPos(0.0f, 0.5f, 0.0f);
	glm::mat4 defObjModel(1.0f);
	defObjModel = glm::translate(defObjModel, defObjPos);
	shaderDefault.activate();
	glUniform1f(glGetUniformLocation(shaderDefault.ID, "scale"), 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderDefault.ID, "model"), 1, GL_FALSE, glm::value_ptr(defObjModel));
	glUniform4f(glGetUniformLocation(shaderDefault.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderDefault.ID, "lightPos"), ligPos.x, ligPos.y, ligPos.z);
}