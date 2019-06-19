#include "HiddenDoor.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "TimeManager.h"

#include <iostream>
#include <GLM/gtx/compatibility.hpp>

HiddenDoor::HiddenDoor(glm::vec3 const& position, glm::vec3 const& close_position, glm::vec3 const& rotation, int t_id) :
	Door(position, rotation, t_id)
{
	m_OpenPosition = close_position;
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("WallTile");
}

void HiddenDoor::Update()
{
	if (m_bOpen)
	{
		double time = TimeManager::GetTime();
		if (time < m_TimeToOpen)
		{
			SetPosition(glm::lerp(m_ClosePosition, m_OpenPosition, (float)(time - m_OpenStart / s_MoveTime)));
			AudioManager::Get()->PlayDoor(m_Position);
		}
	}
}

void HiddenDoor::Open()
{
	if (!m_bOpen)
	{
		m_bOpen = true;

		m_OpenStart = TimeManager::GetTime();
		m_TimeToOpen = m_OpenStart + s_MoveTime;
	}
}

AABB HiddenDoor::GetAABB()
{
	AABB aabb {m_Position, glm::vec3(0.5f)};
	return aabb;
}
