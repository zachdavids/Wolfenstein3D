#include "Medkit.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Player.h"
#include "Camera.h"

#include <GLM/gtc/constants.hpp>

const float LENGTH = 1.0f;
const float HEIGHT = 1.0f;
const float SCALE = 0.2f;

const int HEAL_AMOUNT = 30;

const float PICKUP_DISTANCE = 0.75f;

const int NUM_TEXTURES_X = 1;
const int NUM_TEXTURES_Y = 1;

Medkit::Medkit(glm::vec3 position)
{
	m_Transform.SetPosition(position);
	m_Transform.SetScale(glm::vec3(SCALE));

	m_Shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_Texture = ResourceManager::Get()->GetResource<Texture>("Medkit");
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Billboard");
}

void Medkit::Update()
{
	glm::vec3 player_position = GameManager::Get()->GetPlayer()->m_Transform.GetPosition();
	glm::vec3 camera_direction(player_position.x - m_Transform.GetPosition().x, player_position.y, player_position.z - m_Transform.GetPosition().z);
	float camera_angle = -atanf(camera_direction.z / camera_direction.x) + (90.0f * glm::pi<float>() / 180.0f);

	if (camera_direction.x > 0) {
		camera_angle += glm::pi<float>();
	}
	else {
	}

	m_Transform.SetRotation(0, camera_angle, 0);

	if (glm::length(camera_direction) < PICKUP_DISTANCE) {
		//audio_->PlayMedkit();
		Player::Damage(-HEAL_AMOUNT);
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
