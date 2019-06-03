#pragma once

#include "Transform.h"

#include <glm/vec3.hpp>

class Mesh;
class Texture;
class Shader;

class Wall
{
public:

	enum class Type
	{
		kFloor,
		kCeiling,
		kWall
	};
	
	Wall(glm::vec3 const& position, glm::vec3 const& rotation, Type type);
	void Render();

private:

	glm::vec3 m_Position;
	Transform transform_;
	Mesh* m_Mesh = nullptr;
	Shader* m_Shader = nullptr;
	Texture* m_Texture = nullptr;
};