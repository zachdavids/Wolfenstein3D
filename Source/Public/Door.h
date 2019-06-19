#pragma once

#include "Actor.h"
#include "AABB.h"

class Door : public Actor
{
public:
	
	Door(glm::vec3 const& position, glm::vec3 const& rotatiom, int t_id);
	virtual void Update() override;
	virtual void Open();
	virtual AABB GetAABB();
	static constexpr float s_MoveTime = 1.0f;
	static constexpr float s_Delay = 7.5f;

protected:

	bool m_bOpen;
	double m_OpenStart;
	double m_CloseStart;
	double m_TimeToOpen;
	double m_TimeToClose;
	glm::vec3 m_OpenPosition;
	glm::vec3 m_ClosePosition;
};