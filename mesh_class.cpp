#include "mesh_class.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

Mesh::Mesh() {

	vertDefault = {// Bottom side (neg Y)
	-0.5f,  -0.5f, 0.5f,		0.25, 0.0,		0.0, -1.0, 0.0,
	0.5f, -0.5f, 0.5f,			0.5, 0.0,		0.0, -1.0, 0.0,
	0.5f, -0.5f, -0.5f,			0.5, 0.25,		0.0, -1.0, 0.0,
	-0.5f, -0.5f, -0.5f,		0.25, 0.25,		0.0, -1.0, 0.0,
	// Top side (pos Y)
	-0.5f, 0.5f, 0.5f,			0.25, 0.75,		0.0, 1.0, 0.0,
	0.5f, 0.5f, 0.5f,			0.5, 0.75,		0.0, 1.0, 0.0,
	0.5f, 0.5f, -0.5f,			0.5, 0.5,		0.0, 1.0, 0.0,
	-0.5f, 0.5f, -0.5f,			0.25, 0.5,		0.0, 1.0, 0.0,
	// Front side (pos Z)
	-0.5f, -0.5f, 0.5f,			0.25, 1.0,		0.0, 0.0, 1.0,
	0.5f, -0.5f, 0.5f,			0.5, 1.0,		0.0, 0.0, 1.0,
	-0.5f, 0.5f, 0.5f,			0.25, 0.75,		0.0, 0.0, 1.0,
	0.5f, 0.5f, 0.5f,			0.5, 0.75,		0.0, 0.0, 1.0,
	// Back side (neg Z)
	0.5f, -0.5f, -0.5f,			0.5, 0.25,		0.0, 0.0, -1.0,
	-0.5f, -0.5f, -0.5f,		0.25, 0.25,		0.0, 0.0, -1.0,
	0.5f, 0.5f, -0.5f,			0.5, 0.5,		0.0, 0.0, -1.0,
	-0.5f, 0.5f, -0.5f,			0.25, 0.5,		0.0, 0.0, -1.0,
	// Right side (pos X)
	0.5f, -0.5f, 0.5f,			0.5, 1.0,		1.0, 0.0, 0.0,
	0.5f, -0.5f, -0.5f,			0.75, 1.0,		1.0, 0.0, 0.0,
	0.5f, 0.5f, 0.5f,			0.5, 0.75,		1.0, 0.0, 0.0,
	0.5f, 0.5f, -0.5f,			0.75, 0.75,		1.0, 0.0, 0.0,
	// Left side (neg X)
	-0.5f, -0.5f, 0.5f,			0.25, 1.0,		-1.0, 0.0, 0.0,
	-0.5f, -0.5f, -0.5f,		0.0, 1.0,		-1.0, 0.0, 0.0,
	-0.5f, 0.5f, 0.5f,			0.25, 0.75,		-1.0, 0.0, 0.0,
	-0.5f, 0.5f, -0.5f,			0.0, 0.75,		-1.0, 0.0, 0.0, };

	indiDefault = {
		// Bottom side
		0, 1, 2,
		0, 2, 3,
		// Top side
		4, 5, 6,
		4, 6, 7,
		// Front side
		8, 9, 10,
		9, 10, 11,
		// Back side
		12, 13, 14,
		13, 14, 15,
		// Right side
		16, 17, 18,
		17, 18, 19,
		// Left side
		20, 21, 22,
		21, 22, 23
	};

	vertLigSource = {
		-0.1f, -0.1f, 0.1f,		// 0	  7--------6
		0.1f, -0.1f, 0.1f,		// 1	 /|       /|
		0.1f, -0.1f, -0.1f,		// 2	4--------5 |
		-0.1f, -0.1f, -0.1f,	// 3	| |      | |
		-0.1f, 0.1f, 0.1f,		// 4	| 3------|-2
		0.1f, 0.1f, 0.1f,		// 5	|/       |/
		0.1f, 0.1f, -0.1f,		// 6	0--------1
		-0.1f, 0.1f, -0.1f		// 7
	};

	indiLigSource = {
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};
}

void Mesh::load_obj(std::string inputfile, std::vector<GLfloat>& verticies, std::vector<GLuint>& indicies) {

	tinyobj::ObjReaderConfig reader_config;
	reader_config.mtl_search_path = "./"; // Path to material files

	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(inputfile, reader_config)) {
		if (!reader.Error().empty()) {
			std::cerr << "TinyObjReader: " << reader.Error();
		}
		exit(1);
	}

	if (!reader.Warning().empty()) {
		std::cout << "TinyObjReader: " << reader.Warning();
	}

	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();

	// Loop over shapes
		// Loop over faces(polygon)
		size_t index_offset = 0;
		int temp = 0;
		for (const auto& shape : shapes) {
			// Loop over vertices in the face.
			for (const auto& index : shape.mesh.indices) {
				// access to vertex
				tinyobj::index_t idx = shape.mesh.indices[index_offset];

				//GLfloat temp_vert[] = {attrib.vertices[3 * index.vertex_index + 0], attrib.vertices[3 * index.vertex_index + 1], attrib.vertices[3 * index.vertex_index + 2] };

				verticies.push_back(attrib.vertices[3 * index.vertex_index + 0]);
				verticies.push_back(attrib.vertices[3 * index.vertex_index + 1]);
				verticies.push_back(attrib.vertices[3 * index.vertex_index + 2]);

				verticies.push_back(attrib.texcoords[2 * index.texcoord_index + 0]);
				verticies.push_back(1.0f - attrib.texcoords[2 * index.texcoord_index + 1]);

				// Optional: vertex colors
				verticies.push_back(1.f);

				verticies.push_back(1.f);

				verticies.push_back(1.f);

				indicies.push_back(temp);
				temp++;
				
			}
			index_offset += 3;

			for (long i = 0; i < shape.mesh.indices.size(); i++) {
				//indicies.push_back(shape.mesh.indices[i].vertex_index + 1);
			}
			
		}
}

Mesh::Mesh(std::string obj_path) {
	load_obj(obj_path, vertDefault, indiDefault);
}



std::vector<GLfloat> Mesh::get_vertDefault() { return vertDefault; }
std::vector <GLuint> Mesh::get_indiDefault() { return indiDefault; }
std::vector <GLfloat> Mesh::get_vertLigSource() { return vertLigSource; }
std::vector <GLuint> Mesh::get_indiLigSource() { return indiLigSource; }