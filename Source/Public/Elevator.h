#pragma once

#include "Door.h"

class Elevator : public Door
{
public:

	Elevator(glm::vec3 const& position, glm::vec3 const& rotation, int t_id);
	virtual void Open() override;
	virtual void Update() override;
	static constexpr float s_MoveTime = 0.5f;
};

