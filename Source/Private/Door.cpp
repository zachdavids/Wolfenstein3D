#include "Door.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

#include <GLM/gtx/compatibility.hpp>

const float DOOR_LENGTH = 0.125f;
const float DOOR_WIDTH = 1.0f;
const float DOOR_HEIGHT = 1.0f;

const float TIME_TO_OPEN = 1.0f;
const float DELAY = 3.0f;
const float TIME_TO_CLOSE = 1.0f;

Door::Door(glm::vec3 const& position, bool rotation)
{
	is_open_ = false;

	SetPosition(glm::vec3(position.x + 0.5f, 0, position.z + 0.5f));
	m_OpenPosition = GetPosition();
	m_ClosePosition = GetPosition();

	if (rotation) 
	{
		SetRotation(glm::vec3(0.0f, glm::radians(90.0f), 0.0f));
		m_OpenPosition.z -= 0.9f;
	}
	else
	{
		m_OpenPosition.x += 0.9f;
	}

	m_Shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_Texture = ResourceManager::Get()->GetResource<Texture>("DoorTile");
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Door");
}

void Door::Open()
{
	if (!is_open_) 
	{
		is_open_ = true;

		open_start_ = TimeManager::GetTime();
		open_time_ = open_start_ + TIME_TO_OPEN;
		close_start_ = open_time_ + DELAY;
		close_time_ = close_start_ + TIME_TO_CLOSE;
	}
}

void Door::Update()
{
	if (is_open_)
	{
		double time = TimeManager::GetTime();
		if (time < open_time_) 
		{
			SetPosition(glm::lerp(m_ClosePosition, m_OpenPosition, (float)(time - open_start_ / TIME_TO_OPEN)));
			//audio_->PlayDoorOpen();
		}
		else if (time < close_start_) 
		{
			SetPosition(m_OpenPosition);
		}
		else if (time < close_time_) 
		{
			SetPosition(glm::lerp(m_OpenPosition, m_ClosePosition, (float)(time - close_start_ / TIME_TO_OPEN)));
			//audio_->PlayDoorClose();
		}
		else 
		{
			SetPosition(m_ClosePosition);
			is_open_ = false;
		}
	}
}

void Door::Render()
{
	m_Shader->Bind();
	m_Shader->SetMat4("model", GetModelMatrix());
	m_Texture->Bind();
	m_Mesh->Draw();
}

AABB Door::GetAABB()
{
	AABB aabb;

	if (GetRotation().y == glm::radians(-90.0f)) 
	{
		aabb.m_Min = glm::vec3(-0.0625f, 0.0f, -0.5f) + GetPosition();
		aabb.m_Max = glm::vec3(0.0625f, 0.0f, 0.5f) + GetPosition();
		aabb.m_Position = GetPosition();
	}
	else 
	{
		aabb.m_Min = glm::vec3(-0.5f, 0.0f, -0.0625) + GetPosition();
		aabb.m_Max = glm::vec3(0.5f, 0.0f, 0.0625) + GetPosition();
		aabb.m_Position = GetPosition();
	}

	return aabb;
}