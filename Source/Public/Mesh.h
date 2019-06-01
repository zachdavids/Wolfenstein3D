#ifndef MESH_H
#define MESH_H

#include "Vertex.h"

#include <glew/GL/glew.h>
#include <iostream>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh
{
public:

	static const GLuint position_index_ = 0;
	static const GLuint texture_coord_index_ = 1;
	static const GLuint normal_index_ = 2;

	Mesh();

	void InitializeMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void InitializeMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, bool normal_calculation);
	void LoadMesh(std::string filename);
	void Draw();
	std::vector<Vertex> CalculateNormals(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

private:

	GLuint vao_;
	GLuint vbo_;
	GLuint ibo_;

	int size_;
};

#endif;