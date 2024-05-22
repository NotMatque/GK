#include "shader_buffor_methods.h"

void shader_buffor_init(VAO& vaoDef, VBO& vboDef, EBO& eboDef, VAO vaoLig, VBO vboLig, EBO eboLig, Mesh mesh) {

	VAO t_vaoDef; t_vaoDef.bind();
	VBO t_vboDef(mesh.get_vertDefault()); // VBO of default object
	EBO t_eboDef(mesh.get_indiDefault()); // EBO of default object

	t_vaoDef.linkAttrib(vboDef, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
	t_vaoDef.linkAttrib(vboDef, 1, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	t_vaoDef.linkAttrib(vboDef, 2, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	VAO t_vaoLig; vaoLig.bind();
	VBO t_vboLig(mesh.get_vertLigSource());
	EBO t_eboLig(mesh.get_indiLigSource());

	t_vaoLig.linkAttrib(vboLig, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);

	t_vaoDef.unbind();
	t_vboDef.unbind();
	t_eboDef.unbind();

	t_vaoLig.unbind();
	t_vboLig.unbind();
	t_eboLig.unbind();

	vaoDef = t_vaoDef;
	vboDef = t_vboDef;
	eboDef = t_eboDef;

	vaoLig = t_vaoLig;
	vboLig = t_vboLig;
	eboLig = t_eboLig;


}

void shader_buffor_terminate(VAO& vaoDef, VBO& vboDef, EBO& eboDef,
							 VAO vaoLig, VBO vboLig, EBO eboLig,
							 Shader& shaderDefault, Shader& shaderLig) {

	vboDef.destroy();
	vaoDef.destroy();
	eboDef.destroy();
	shaderDefault.destroy();
	vboLig.destroy();
	vaoLig.destroy();
	eboLig.destroy();
	shaderLig.destroy();
}