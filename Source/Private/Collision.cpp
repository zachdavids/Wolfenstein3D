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

glm::vec3 Collision::CheckIntersection(glm::vec3 line_start, glm::vec3 line_end, bool attack)
{
	glm::vec3 nearest_intersection(NULL);

	//for (unsigned int i = 0; i < m_LevelGeometry.size(); i++)
	//{
	//	glm::vec3 collision_vector = LineIntersection(line_start, line_end, m_LevelGeometry[i].m_Mesh->m_AABB.m_Min, collision_end[i]);

	//	if (collision_vector != glm::vec3(NULL) && nearest_intersection == glm::vec3(NULL) ||
	//		glm::length(nearest_intersection - line_start) > glm::length(collision_vector - line_start))
	//	{
	//		nearest_intersection = NearestIntersection(nearest_intersection, collision_vector, line_start);
	//	}
	//}

	//for (unsigned int i = 0; i < doors_temp_.size(); i++)
	//{
	//	glm::vec3 collision_vector = LineIntersectionRectangle(line_start, line_end, doors_temp_[i].GetPosition(), doors_temp_[i].GetDimensions().x, doors_temp_[i].GetDimensions().y);

	//	if (collision_vector != glm::vec3(NULL) && nearest_intersection == glm::vec3(NULL) ||
	//		glm::length(nearest_intersection - line_start) > glm::length(collision_vector - line_start))
	//	{
	//		nearest_intersection = NearestIntersection(nearest_intersection, collision_vector, line_start);
	//	}
	//}

	//if (attack)
	//{
	//	glm::vec3 nearest_enemy_intersection(NULL);
	//	glm::vec3 collision_vector(NULL);

	//	for (unsigned int i = 0; i < enemies_temp_.size(); i++)
	//	{
	//		glm::vec3 collision_vector = LineIntersectionRectangle(line_start, line_end, enemies_temp_[i].GetTranslation(), enemies_temp_[i].GetSize().x, enemies_temp_[i].GetSize().y);

	//		glm::vec3 last_enemy_intersection = nearest_enemy_intersection;
	//		nearest_enemy_intersection = NearestIntersection(nearest_intersection, collision_vector, line_start);

	//		if (nearest_enemy_intersection == collision_vector)
	//		{
	//			nearest_enemy_num = i;
	//		}
	//	}
	//}

	return nearest_intersection;
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

glm::vec3 Collision::LineIntersectionRectangle(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 position, float width, float length)
{
	glm::vec3 result = glm::vec3(NULL);

	//glm::vec3 collision_vector = LineIntersection(line_start, line_end, position, glm::vec3(position.x + width, 0, position.z));
	//result = NearestIntersection(result, collision_vector, line_start);

	//collision_vector = LineIntersection(line_start, line_end, position, glm::vec3(position.x, 0, position.z + length));
	//result = NearestIntersection(result, collision_vector, line_start);

	//collision_vector = LineIntersection(line_start, line_end, glm::vec3(position.x, 0, position.z + length), glm::vec3(position.x + width, 0, position.z + length));
	//result = NearestIntersection(result, collision_vector, line_start);

	//collision_vector = LineIntersection(line_start, line_end, glm::vec3(position.x + width, 0, position.z), glm::vec3(position.x + width, 0, position.z + length));
	//result = NearestIntersection(result, collision_vector, line_start);

	return result;
}

glm::vec3 Collision::NearestIntersection(glm::vec3 line_1, glm::vec3 line_2, glm::vec3 nearest)
{
	//if (line_2 != glm::vec3(NULL) && line_1 == glm::vec3(NULL) ||
	//	glm::length(line_1 - nearest) > glm::length(line_2 - nearest))
	//{
	//	return line_2;
	//}
	//return line_1;
	return glm::vec3(0.0f);
}