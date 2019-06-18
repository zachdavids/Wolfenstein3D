#pragma once

#include "Actor.h"

class Item : public Actor
{
public:

	Item(glm::vec3 const& position, int t_id);
	void Update() override;
};

