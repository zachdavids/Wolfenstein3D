#include "Medkit.h"
#include "ResourceManager.h"
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
	m_Transform.SetCamera(Player::GetCamera());
}

void Medkit::Update()
{
	glm::vec3 camera_direction(m_Transform.GetCamera()->GetPosition().x - m_Transform.GetPosition().x, m_Transform.GetCamera()->GetPosition().y, m_Transform.GetCamera()->GetPosition().z - m_Transform.GetPosition().z);
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
	Shader* shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	shader->Bind();
	shader->SetMat4("transform", m_Transform.GetModelProjection());
	ResourceManager::Get()->GetResource<Texture>("Medkit")->Bind();
	ResourceManager::Get()->GetResource<Mesh>("Billboard")->Draw();
}

bool Medkit::GetEaten()
{
	return m_bIsEaten;
}
