#include "Collision.h"

#include <algorithm>

glm::vec3 Collision::CheckCollision(glm::vec3 old_position, glm::vec3 new_position, float width, float length)
{
	glm::vec3 collision_vector = glm::vec3(1, 0, 1);
	//glm::vec3 movement_vector = new_position - old_position;

	//if (movement_vector.length() > 0)
	//{
	//	// Wall Collision
	//	glm::vec3 node_size(1, 0, 1);
	//	glm::vec3 object_size(width, 0, length);

	//	glm::vec3 old_position_2(old_position.x + 1, 0, old_position.z);
	//	glm::vec3 new_position_2(new_position.x + 1, 0, new_position.z);

	//	for (unsigned int i = 0; i < dimensions_.x; i++)
	//	{
	//		for (unsigned int j = 0; j < dimensions_.y; j++)
	//		{
	//			if (!nodes_[(i - 1) * dimensions_.x + j].m_Node.test(Node::NodeType::Location))
	//			{
	//				collision_vector *= RectangularCollision(old_position_2, new_position_2, object_size, node_size * glm::vec3(i, 0, j), node_size);
	//			}
	//		}
	//	}

	//	// Door Collision
	//	old_position_2.x = old_position.x;
	//	new_position_2.x = new_position.x;

	//	for (unsigned int i = 0; i < doors_temp_.size(); i++)
	//	{
	//		node_size = doors_temp_[i].GetDimensions();
	//		collision_vector *= RectangularCollision(old_position_2, new_position_2, object_size, doors_temp_[i].GetPosition(), node_size);
	//	}
	//}

	return collision_vector;
}

glm::vec3 Collision::RectangularCollision(glm::vec3 old_position, glm::vec3 new_position, glm::vec3 size_1, glm::vec3 position_2, glm::vec3 size_2)
{
	glm::vec3 result(0.0f);

	//if ((new_position.x + size_1.x < position_2.x) || (new_position.x - size_1.x > position_2.x + size_2.x * size_2.x) ||
	//	(old_position.z + size_1.z < position_2.z) || (old_position.z - size_1.z > position_2.z + size_2.z * size_2.z))
	//{
	//	result.x = 1;
	//}

	//if ((old_position.x + size_1.x < position_2.x) || (old_position.x - size_1.x > position_2.x + size_2.x * size_2.x) ||
	//	(new_position.z + size_1.z < position_2.z) || (new_position.z - size_1.z > position_2.z + size_2.z * size_2.z))
	//{
	//	result.z = 1;
	//}

	return result;
}

bool Collision::RayAABBIntersection(Ray ray, AABB box)
{
	double tx1 = (box.m_Min.x - ray.m_Origin.x) * ray.m_InvDirection.x;
	double tx2 = (box.m_Max.x - ray.m_Origin.x) * ray.m_InvDirection.x;

	double tmin = std::min(tx1, tx2);
	double tmax = std::max(tx1, tx2);

	double ty1 = (box.m_Min.y - ray.m_Origin.y) * ray.m_InvDirection.y;
	double ty2 = (box.m_Max.y - ray.m_Origin.y) * ray.m_InvDirection.y;

	tmin = std::max(tmin, std::min(ty1, ty2));
	tmax = std::min(tmax, std::max(ty1, ty2));

	return tmax >= tmin;
}