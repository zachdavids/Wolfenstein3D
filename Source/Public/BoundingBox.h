#pragma once

#include <GLM/vec3.hpp>

struct BoundingBox
{
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 half = glm::vec3(0.0f);
};