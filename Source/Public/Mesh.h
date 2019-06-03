#pragma once

#include "Vertex.h"
#include "Resource.h"

#include <vector>

struct aiNode;
struct aiScene;
struct aiMesh;

class Mesh : public Resource
{
public:

	Mesh(std::string const& path);
	void Create();
	void ProcessMesh(aiNode* node, const aiScene* scene);
	void CreateVertices(aiMesh* mesh);
	void CreateIndices(aiMesh* mesh);
	void Draw() const;

private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	void CreateVAO();
	void CreateEBO();
	void CreateVBO();
	void EnableAttributes() const;
	void UnbindVAO() const;
};