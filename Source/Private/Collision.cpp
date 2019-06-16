#include "Collision.h"

#include <algorithm>
#include <iostream>

#include <GLM/glm.hpp>

bool Collision::AABBIntersection(AABB const& box_one, AABB const& box_two, glm::vec3& normal, glm::vec3& position)
{
	double dx = box_two.position.x - box_one.position.x;
	double px = (box_two.half.x + box_one.half.x) - glm::abs(dx);
	if (px <= 0)
	{
		return false;
	}

	double dz = box_two.position.z - box_one.position.z;
	double pz = (box_two.half.z + box_one.half.z) - glm::abs(dz);
	if (pz <= 0)
	{
		return false;
	}

	if (px < pz)
	{
		normal.x = 0;
		position.x = px * glm::sign(dx);
	}
	else
	{
		normal.z = 0;
		position.z = pz * glm::sign(dz);
	}

	return true;
}

bool Collision::RayAABBIntersection(Ray const& ray, AABB const& box)
{
	double tx1 = (box.position.x - box.half.x - ray.m_Origin.x) * ray.m_InvDirection.x;
	double tx2 = (box.position.x + box.half.x - ray.m_Origin.x) * ray.m_InvDirection.x;

	double tmin = std::min(tx1, tx2);
	double tmax = std::max(tx1, tx2);

	double ty1 = (box.position.z - box.half.z - ray.m_Origin.z) * ray.m_InvDirection.z;
	double ty2 = (box.position.z + box.half.z - ray.m_Origin.z) * ray.m_InvDirection.z;

	tmin = std::max(tmin, std::min(ty1, ty2));
	tmax = std::min(tmax, std::max(ty1, ty2));

	return tmax >= 0 && tmax >= tmin;
}
