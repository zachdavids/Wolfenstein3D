#include "Door.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "TimeManager.h"

#include <GLM/gtx/compatibility.hpp>

Door::Door(glm::vec3 const& position, glm::vec3 const& rotation, int t_id)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Tid = t_id;
	m_ClosePosition = position;
	m_OpenPosition = position;
	m_bOpen = false;
	rotation.y == glm::radians(90.0f) ? m_OpenPosition.x += 0.9f : m_OpenPosition.z += 0.9f;
	m_Shader = ResourceManager::Get()->GetResource<Shader>("TileShader");
	m_Texture = ResourceManager::Get()->GetResource<TextureArray>("SpriteSheet");
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Door");
}

void Door::Open()
{
	if (!m_bOpen) 
	{
		m_bOpen = true;

		m_OpenStart = TimeManager::GetTime();
		m_TimeToOpen = m_OpenStart + s_MoveTime;
		m_CloseStart = m_TimeToOpen + s_Delay;
		m_TimeToClose = m_CloseStart + s_MoveTime;
	}
}

void Door::Update()
{
	if (m_bOpen)
	{
		double time = TimeManager::GetTime();
		if (time < m_TimeToOpen) 
		{
			SetPosition(glm::lerp(m_ClosePosition, m_OpenPosition, (float)(time - m_OpenStart / s_MoveTime)));
			AudioManager::Get()->PlayDoor(m_Position);
		}
		else if (time < m_CloseStart) 
		{
			SetPosition(m_OpenPosition);
		}
		else if (time < m_TimeToClose) 
		{
			SetPosition(glm::lerp(m_OpenPosition, m_ClosePosition, (float)(time - m_CloseStart / s_MoveTime)));
			AudioManager::Get()->PlayDoor(m_Position);
		}
		else 
		{
			SetPosition(m_ClosePosition);
			m_bOpen = false;
		}
	}
}

BoundingBox Door::GetBoundingBox()
{
	if (GetRotation().y == glm::radians(-90.0f)) 
	{
		return BoundingBox{ m_Position, glm::vec3(0.0625f, 0.0f, 0.5f) };
	}
	else 
	{
		return BoundingBox{ m_Position, glm::vec3(0.5f, 0.0f, 0.0625) };
	}
}