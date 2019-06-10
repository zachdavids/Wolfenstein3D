#include "Collision.h"

#include <algorithm>

bool Collision::AABBIntersection(AABB& box_one, AABB& box_two)
{
	double d1x = box_two.m_Min.x - box_one.m_Max.x;
	double d1z = box_two.m_Min.z - box_one.m_Max.z;
	double d2x = box_one.m_Min.x - box_two.m_Max.x;
	double d2z = box_one.m_Min.z - box_two.m_Max.z;

	bool d1 = d1x > 0.0 || d1z > 0.0;
	bool d2 = d2x > 0.0 || d2z > 0.0;
	
	return !(d1 || d2);
}

bool Collision::RayAABBIntersection(Ray& ray, AABB& box)
{
	double tx1 = (box.m_Min.x - ray.m_Origin.x) * ray.m_InvDirection.x;
	double tx2 = (box.m_Max.x - ray.m_Origin.x) * ray.m_InvDirection.x;

	double tmin = std::min(tx1, tx2);
	double tmax = std::max(tx1, tx2);

	double ty1 = (box.m_Min.z - ray.m_Origin.z) * ray.m_InvDirection.z;
	double ty2 = (box.m_Max.z - ray.m_Origin.z) * ray.m_InvDirection.z;

	tmin = std::max(tmin, std::min(ty1, ty2));
	tmax = std::min(tmax, std::max(ty1, ty2));

	return tmax >= 0 && tmax >= tmin;
}