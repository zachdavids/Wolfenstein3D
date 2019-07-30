#pragma once

#include <vector>

#include <GLM/vec3.hpp>

class DebugMesh
{
public:

	DebugMesh(std::vector<glm::vec3> const& vertices);
	void Draw() const;

private:

	void CreateVAO();
	void CreateVBO();
	void EnableAttributes() const;
	void UnbindVAO() const;

private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;
	std::vector<glm::vec3> m_Vertices;
};

