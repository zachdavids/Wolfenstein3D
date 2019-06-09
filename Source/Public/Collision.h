#pragma once

#include "AABB.h"
#include "Ray.h"

#include <GLM/vec3.hpp>

namespace Collision
{
	glm::vec3 CheckCollision(glm::vec3 old_position, glm::vec3 new_position, float width, float length);
	glm::vec3 RectangularCollision(glm::vec3 old_position, glm::vec3 new_position, glm::vec3 size_1, glm::vec3 position_2, glm::vec3 size_2);
	bool RayAABBIntersection(Ray ray, AABB box);
}

