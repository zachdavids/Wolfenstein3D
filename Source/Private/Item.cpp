#include "Item.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Player.h"
#include "TextureArray.h"
#include "Shader.h"
#include "Mesh.h"

#include <GLM/gtc/constants.hpp>

Item::Item(glm::vec3 const& position, int t_id) : 
	m_Tid(t_id)
{
	SetPosition(position);

	m_Shader = ResourceManager::Get()->GetResource<Shader>("TileShader");
	m_Texture = ResourceManager::Get()->GetResource<TextureArray>("SpriteSheet");
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Billboard");
}

void Item::Update()
{
	glm::vec3 player_position = GameManager::Get()->GetPlayer()->GetCamera()->GetPosition();
	glm::vec3 camera_direction = player_position - GetPosition();

	float camera_angle = -atanf(camera_direction.z / camera_direction.x) + (90.0f * glm::pi<float>() / 180.0f);
	if (camera_direction.x > 0)
	{
		camera_angle += glm::pi<float>();
	}
	SetRotation(glm::vec3(0, camera_angle, 0));
}

void Item::Render()
{
	m_Shader->Bind();
	m_Shader->SetMat4("model", GetModelMatrix());
	m_Shader->SetInt("index", m_Tid);
	m_Texture->Bind();
	m_Mesh->Draw();
}
