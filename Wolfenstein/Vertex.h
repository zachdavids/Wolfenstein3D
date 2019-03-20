#pragma once

#include <glm.hpp>

struct Vertex
{
public:
	glm::vec3 position_;
	glm::vec2 texture_coord_;
	glm::vec3 normal_;
};