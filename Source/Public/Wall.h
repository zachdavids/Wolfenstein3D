#pragma once

#include "Actor.h"
#include "AABB.h"

#include <glm/vec3.hpp>

class Mesh;
class Texture;
class Shader;

class Wall : public Actor
{
public:

	enum class Type
	{
		kFloor,
		kCeiling,
		kWall
	};
	
	Wall(glm::vec3 const& position, glm::vec3 const& rotation, Type type);
	virtual void Render() override;
	AABB GetAABB();

private:

	Mesh* m_Mesh = nullptr;
	Shader* m_Shader = nullptr;
	Texture* m_Texture = nullptr;
};