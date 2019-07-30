#pragma once

#include "DebugMesh.h"

#include <list>
#include <GLM/vec3.hpp>

class Shader;

class DebugDrawManager
{
public:

	struct DebugObject
	{
		bool depth;
		double spawn_time;
		double duration;
		glm::vec3 color;
		DebugMesh mesh;
	};

	DebugDrawManager();
	void Update();
	void DrawDebugMeshes() const;
	void AddLine();
	void AddAxes();
	void AddSphere(glm::vec3 const& center, float radius, glm::vec3 const& color, float duration = 0.0f, bool depth_test = true);

private:

	Shader* m_Shader;
	std::list<DebugObject> m_DebugObjects;
};

