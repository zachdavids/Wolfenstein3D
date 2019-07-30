#include "DebugMesh.h"

#include <glad.h>

DebugMesh::DebugMesh(std::vector<glm::vec3> const& vertices) :
	m_Vertices(vertices)
{
}

void DebugMesh::Draw() const
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, m_Vertices.size());
	glBindVertexArray(0);
}

void DebugMesh::CreateVAO()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
}

void DebugMesh::CreateVBO()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(glm::vec3), &m_Vertices[0], GL_STATIC_DRAW);
}

void DebugMesh::EnableAttributes() const
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
}

void DebugMesh::UnbindVAO() const
{
	glBindVertexArray(0);
}
