#pragma once

#include "AABB.h"
#include "Ray.h"

#include <GLM/vec3.hpp>

namespace Collision
{
	glm::vec3 CheckCollision(glm::vec3 old_position, glm::vec3 new_position, float width, float length);
	glm::vec3 RectangularCollision(glm::vec3 old_position, glm::vec3 new_position, glm::vec3 size_1, glm::vec3 position_2, glm::vec3 size_2);
	glm::vec3 CheckIntersection(glm::vec3 line_start, glm::vec3 line_end, bool attack);
	bool RayAABBIntersection(Ray ray, AABB box);
	glm::vec3 LineIntersectionRectangle(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 position, float width, float length);
	glm::vec3 NearestIntersection(glm::vec3 line_1, glm::vec3 line_2, glm::vec3 nearest);
}

