#include "Elevator.h"
#include "AudioManager.h"
#include "TimeManager.h"
#include "GameManager.h"
#include "ResourceManager.h"

#include <iostream>

Elevator::Elevator(glm::vec3 const& position, glm::vec3 const& rotation, int t_id) :
	Door(position, rotation, t_id)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Tid = t_id;
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("WallTile");
}

void Elevator::Open()
{
	if (!m_bOpen)
	{
		m_bOpen = true;
		m_Tid -= 2;

		m_OpenStart = TimeManager::GetTime();
		m_TimeToOpen = m_OpenStart + s_MoveTime;
	}
}

void Elevator::Update()
{
	if (m_bOpen)
	{
		double time = TimeManager::GetTime();
		if (time < m_TimeToOpen)
		{
			AudioManager::Get()->PlayDoor(m_Position);
		}
		else
		{
			GameManager::Get()->EndGame();
		}
	}
}