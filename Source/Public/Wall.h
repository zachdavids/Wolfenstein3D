#pragma once

#include "Transform.h"

#include <glm/vec3.hpp>

class Mesh;
class Texture;

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
	glm::vec3 GetDimensions();
	glm::vec3 GetTranslation() { return transform_.GetTranslation(); };
	glm::vec3 GetPosition() { return m_Position; };
	void SetPosition(glm::vec3 position) { m_Position = position; };

private:

	Mesh* m_Mesh;
	Texture* m_Texture;
	glm::vec3 m_Position;
	Transform transform_;
};