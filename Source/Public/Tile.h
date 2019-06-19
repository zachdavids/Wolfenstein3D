#pragma once

#include "Actor.h"

class Tile : public Actor
{
public:
	
	Tile(glm::vec3 const& position, glm::vec3 const& rotation, int t_id, Mesh* mesh);
	virtual void Update() override {};
};