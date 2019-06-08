#include "Mesh.h"

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Mesh::Mesh(std::string const& path) : Resource(path)
{
}

void Mesh::Create()
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(m_Path, aiProcess_TransformUVCoords | aiProcessPreset_TargetRealtime_MaxQuality);
	ProcessMesh(scene->mRootNode, scene);

	CreateVAO();
	CreateEBO();
	CreateVBO();
	EnableAttributes();
	UnbindVAO();
}

void Mesh::ProcessMesh(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i != node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		CreateVertices(mesh);
		CreateIndices(mesh);
	}
	for (unsigned int i = 0; i != node->mNumChildren; ++i)
	{
		ProcessMesh(node->mChildren[i], scene);
	}
}

void Mesh::CreateVertices(aiMesh* mesh)
{
	for (unsigned int i = 0; i != mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		vertex.m_Position.x = mesh->mVertices[i].x;
		vertex.m_Position.y = mesh->mVertices[i].y;
		vertex.m_Position.z = mesh->mVertices[i].z;

		m_AABB.m_Min.x = std::min(m_AABB.m_Min.x, vertex.m_Position.x);
		m_AABB.m_Min.y = std::min(m_AABB.m_Min.y, vertex.m_Position.y);
		m_AABB.m_Min.z = std::min(m_AABB.m_Min.z, vertex.m_Position.z);

		m_AABB.m_Max.x = std::max(m_AABB.m_Max.x, vertex.m_Position.x);
		m_AABB.m_Max.y = std::max(m_AABB.m_Max.y, vertex.m_Position.y);
		m_AABB.m_Min.z = std::min(m_AABB.m_Min.z, vertex.m_Position.z);

		if (mesh->HasTextureCoords(0))
		{
			vertex.m_UV.x = mesh->mTextureCoords[0][i].x;
			vertex.m_UV.y = mesh->mTextureCoords[0][i].y;
		}
		m_Vertices.emplace_back(vertex);
	}
}

void Mesh::CreateIndices(aiMesh* mesh)
{
	for (unsigned int i = 0; i != mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j != face.mNumIndices; ++j)
		{
			m_Indices.emplace_back(face.mIndices[j]);
		}
	}
}

glm::vec3 Mesh::GetSize()
{
	return m_AABB.m_Max - m_AABB.m_Min;
}

AABB& Mesh::GetAABB()
{
	return m_AABB;
}

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
}

void Mesh::CreateEBO()
{
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);
}

void Mesh::CreateVBO()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);
}

void Mesh::EnableAttributes() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_UV));
}

void Mesh::UnbindVAO() const
{
	glBindVertexArray(0);
}

void Mesh::Draw() const
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

