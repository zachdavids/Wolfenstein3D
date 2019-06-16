#pragma once

#include "AABB.h"
#include "Ray.h"

namespace Collision
{
	bool AABBIntersection(AABB const& box_one, AABB const& box_two, glm::vec3& collision, glm::vec3& position);
	bool RayAABBIntersection(Ray const& ray, AABB const& box);
}

