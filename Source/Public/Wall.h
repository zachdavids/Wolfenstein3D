#pragma once

#include "Actor.h"
#include "AABB.h"

#include <glm/vec3.hpp>

class Mesh;
class TextureArray;
class Shader;

class Wall : public Actor
{
public:
	
	Wall(glm::vec3 const& position, glm::vec3 const& rotation, int t_id, Mesh* mesh);
	virtual void Render() override;

private:

	int m_Tid;
	glm::mat4 m_Model;
	Mesh* m_Mesh = nullptr;
	Shader* m_Shader = nullptr;
	TextureArray* m_Texture = nullptr;
};