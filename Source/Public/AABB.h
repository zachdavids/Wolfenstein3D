#pragma once

#include <GLM/vec2.hpp>

struct AABB
{
	glm::vec3 m_Min = glm::vec3(0.0f);
	glm::vec3 m_Max = glm::vec3(0.0f);
};