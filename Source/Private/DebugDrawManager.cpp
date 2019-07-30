#include "DebugDrawManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Shader.h"

#include <vector>
#include <glad.h>
#include <GLM/trigonometric.hpp>
#include <GLM/gtc/constants.hpp>

DebugDrawManager::DebugDrawManager()
{
	m_Shader = ResourceManager::Get()->GetResource<Shader>("DebugShader");
}

void DebugDrawManager::Update()
{
	for (auto it = m_DebugObjects.begin(); it != m_DebugObjects.end(); ++it)
	{
		if (TimeManager::GetTime() - it->spawn_time >= it->duration)
		{
			m_DebugObjects.erase(it);
		}
	}
}

void DebugDrawManager::AddLine()
{
}

void DebugDrawManager::AddAxes()
{
}

void DebugDrawManager::AddSphere(glm::vec3 const& center, float radius, glm::vec3 const& color, float duration /*= 0.0f*/, bool depth_test /*= true*/)
{
	std::vector<glm::vec3> vertices;
	for (float phi = 0.; phi < 2 * glm::pi<float>(); phi += glm::pi<float>() / 8)
	{
		for (float theta = 0.; theta < glm::pi<float>(); theta += glm::pi<float>() / 8)
		{
			glm::vec3 vertex;
			vertex.x = radius * glm::cos(phi) * glm::sin(theta) + center.x;
			vertex.y = radius * glm::sin(phi) * glm::sin(theta) + center.y;
			vertex.z = radius * glm::cos(theta) + center.z;
			vertices.push_back(vertex);
		}
	}

	m_DebugObjects.emplace_back(DebugObject{depth_test, TimeManager::GetTime(), duration, color, DebugMesh(vertices)});
}

void DebugDrawManager::DrawDebugMeshes() const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (DebugObject const& object : m_DebugObjects)
	{
		if (object.depth == false)
		{
			glDisable(GL_DEPTH_TEST);
		}

		m_Shader->SetVec3("color", object.color);
		object.mesh.Draw();

		glEnable(GL_DEPTH_TEST);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}