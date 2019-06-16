#include "Door.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Shader.h"
#include "TextureArray.h"
#include "Mesh.h"

#include <iostream>
#include <GLM/gtx/compatibility.hpp>

const float DOOR_LENGTH = 0.125f;
const float DOOR_WIDTH = 1.0f;
const float DOOR_HEIGHT = 1.0f;

const float TIME_TO_OPEN = 1.0f;
const float DELAY = 3.0f;
const float TIME_TO_CLOSE = 1.0f;

Door::Door(glm::vec3 const& position, glm::vec3 const& rotation, int t_id) :
	m_Tid(t_id)
{
	SetPosition(position);
	SetRotation(rotation);

	m_ClosePosition = GetPosition();
	m_OpenPosition = GetPosition();
	rotation.y == glm::radians(90.0f) ? m_OpenPosition.x += 0.9f : m_OpenPosition.z += 0.9f;

	m_Shader = ResourceManager::Get()->GetResource<Shader>("TileShader");
	m_Texture = ResourceManager::Get()->GetResource<TextureArray>("SpriteSheet");
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
	m_Shader->SetInt("index", m_Tid);
	m_Texture->Bind();
	m_Mesh->Draw();
}

AABB Door::GetAABB()
{
	AABB aabb;

	if (GetRotation().y == glm::radians(-90.0f)) 
	{
		aabb.position = GetPosition(); 
		aabb.half = glm::vec3(0.0625f, 0.0f, 0.5f);
	}
	else 
	{
		aabb.position = GetPosition();
		aabb.half = glm::vec3(0.5f, 0.0f, 0.0625);
	}

	return aabb;
}