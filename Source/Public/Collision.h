#pragma once

#include "BoundingBox.h"
#include "Ray.h"

namespace Collision
{
	bool BoundingBoxIntersection(BoundingBox const& box_one, BoundingBox const& box_two, glm::vec3& collision, glm::vec3& position);
	bool RayBoundingBoxIntersection(Ray const& ray, BoundingBox const& box);
}

