#pragma once

#include "Actor.h"

class Medkit : public Actor
{
public:

	Medkit(glm::vec3 position);

	virtual void Update() override;
	virtual void Render() override;
	bool GetEaten();

private:

	bool m_bIsEaten = false;
};