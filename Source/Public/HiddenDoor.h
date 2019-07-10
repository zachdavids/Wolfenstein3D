#pragma once

#include "Door.h"

class HiddenDoor :
	public Door
{
public:
	HiddenDoor(glm::vec3 const& position, glm::vec3 const& close_position, glm::vec3 const& rotation, int t_id);
	virtual void Update() override;
	virtual void Open() override;
	virtual BoundingBox GetBoundingBox() override;
};

