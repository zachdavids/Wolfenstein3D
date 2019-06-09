#pragma once

#include <GLM/vec3.hpp>

struct Ray
{
	glm::vec3 m_Origin;
	glm::vec3 m_Direction;
	glm::vec3 m_InvDirection;
};