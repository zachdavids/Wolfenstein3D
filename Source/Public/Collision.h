#pragma once

#include "AABB.h"
#include "Ray.h"

#include <GLM/vec3.hpp>

namespace Collision
{
	bool AABBIntersection(AABB& box_one, AABB& box_two);
	bool RayAABBIntersection(Ray ray, AABB box);
}

