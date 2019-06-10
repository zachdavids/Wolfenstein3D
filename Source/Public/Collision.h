#pragma once

#include "AABB.h"
#include "Ray.h"

namespace Collision
{
	bool AABBIntersection(AABB& box_one, AABB& box_two);
	bool RayAABBIntersection(Ray& ray, AABB& box);
}

