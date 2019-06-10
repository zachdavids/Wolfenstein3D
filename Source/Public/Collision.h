#pragma once

#include "AABB.h"
#include "Ray.h"

namespace Collision
{
	bool AABBIntersection(AABB const& box_one, AABB const& box_two);
	bool RayAABBIntersection(Ray const& ray, AABB const& box);
}

