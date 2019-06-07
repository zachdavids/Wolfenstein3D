#include "Medkit.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Player.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/constants.hpp>

const int Medkit::m_HealAmount = 30;
const float Medkit::m_PickupDistance = 0.5f;

Medkit::Medkit(glm::vec3 position)
{
	m_Transform.SetPosition(position);
	m_Transform.SetScale(glm::vec3(0.2f));

	m_Shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_Texture = ResourceManager::Get()->GetResource<Texture>("Medkit");
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Billboard");
}

void Medkit::Update()
{
	glm::vec3 player_position = GameManager::Get()->GetPlayer()->m_Transform.GetPosition();
	glm::vec3 camera_direction = player_position - m_Transform.GetPosition();

	float camera_angle = -atanf(camera_direction.z / camera_direction.x) + (90.0f * glm::pi<float>() / 180.0f);
	if (camera_direction.x > 0) 
	{
		camera_angle += glm::pi<float>();
	}
	m_Transform.SetRotation(0, camera_angle, 0);

	if (glm::length(camera_direction) < m_PickupDistance) 
	{
		AudioManager::Get()->PlayMedkit();
		Player::Damage(-m_HealAmount);
		m_bIsEaten = true;
	}
}

void Medkit::Render()
{
	m_Shader->Bind();
	m_Shader->SetMat4("model", m_Transform.GetModelMatrix());
	m_Texture->Bind();
	m_Mesh->Draw();
}

bool Medkit::GetEaten()
{
	return m_bIsEaten;
}
