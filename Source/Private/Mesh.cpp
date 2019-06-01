#include "Mesh.h"

Mesh::Mesh()
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ibo_);
	size_ = 0;
}

void Mesh::InitializeMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	InitializeMesh(vertices, indices, false);
}

void Mesh::InitializeMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, bool normal_calculation)
{
	if (normal_calculation) {
		vertices = CalculateNormals(vertices, indices);
	}

	size_ = indices.size();// * Vertex::SIZE;

	glBindVertexArray(vao_);

	// Vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(position_index_, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(texture_coord_index_, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(glm::vec3));
	glVertexAttribPointer(normal_index_, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	// Indices Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
}

void Mesh::Draw()
{
	glBindVertexArray(vao_);

	glEnableVertexAttribArray(position_index_);
	glEnableVertexAttribArray(texture_coord_index_);
	glEnableVertexAttribArray(normal_index_);

	glDrawElementsBaseVertex(GL_TRIANGLES, size_, GL_UNSIGNED_INT, 0, 0);

	glDisableVertexAttribArray(position_index_);
	glDisableVertexAttribArray(texture_coord_index_);
	glDisableVertexAttribArray(normal_index_);

	glBindVertexArray(0);
}

void Mesh::LoadMesh(std::string filename)
{
	std::vector<Vertex> data;
	std::vector<unsigned int> indices;

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filename.c_str(),
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace);

	if (!scene)
	{
		std::cout << "Mesh load failed!: " << filename << std::endl;
		//assert(0 == 0);
	}

	const aiMesh* model = scene->mMeshes[0];

	const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
	for (unsigned int i = 0; i < model->mNumVertices; i++)
	{
		const aiVector3D vertex = model->mVertices[i];

		data.push_back(glm::vec3(vertex.x, vertex.y, vertex.z));
	}

	for (unsigned int i = 0; i < model->mNumFaces; i++)
	{
		const aiFace& face = model->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}

	InitializeMesh(data, indices, true);
}

std::vector<Vertex> Mesh::CalculateNormals(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	for (unsigned int i = 0; i < indices.size(); i += 3) {
		int index_1 = indices[i];
		int index_2 = indices[i + 1];
		int index_3 = indices[i + 2];

		glm::vec3 vertex_1 = vertices[index_2].GetPosition() - vertices[index_1].GetPosition();
		glm::vec3 vertex_2 = vertices[index_3].GetPosition() - vertices[index_1].GetPosition();

		glm::vec3 normal = glm::normalize(glm::cross(vertex_1, vertex_2));

		vertices[index_1].SetNormal(glm::normalize(vertices[index_1].GetNormal() + normal));
		vertices[index_2].SetNormal(glm::normalize(vertices[index_2].GetNormal() + normal));
		vertices[index_3].SetNormal(glm::normalize(vertices[index_3].GetNormal() + normal));
	}
	return vertices;
}

