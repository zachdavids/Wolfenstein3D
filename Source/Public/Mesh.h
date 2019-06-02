#pragma once

#include "Vertex.h"

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <GLM/glm.hpp>

class Mesh
{
public:

	Mesh();
	Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices);
	void Create();
	void InitializeMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void Draw();

private:

	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	void CreateVAO();
	void CreateEBO();
	void CreateVBO();
	void EnableAttributes() const;
	void UnbindVAO() const;

	int size_;
};