#include "Pickup.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Player.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/constants.hpp>

const float Pickup::s_PickupDistance = 1.0f;

Pickup::Pickup(glm::vec3 const& position, Type type, int t_id, int amount) :
	Item(position, t_id),
	m_Type(type),
	m_Amount(amount)
{
	SetPosition(position);
}

void Pickup::Update()
{
	if (m_bIsEaten == false)
	{
		Item::Update();

		glm::vec3 player_position = GameManager::Get()->GetPlayer()->GetCamera()->GetPosition();
		glm::vec3 camera_direction = player_position - GetPosition();

		if (glm::length(camera_direction) < s_PickupDistance)
		{
			switch (m_Type)
			{
			case kHeal:
				if (GameManager::Get()->GetPlayer()->GetHealth() < GameManager::Get()->GetPlayer()->GetMaxHealth())
				{
					AudioManager::Get()->PlayMedkit(GetPosition());
					GameManager::Get()->GetPlayer()->Damage(-m_Amount);
					m_bIsEaten = true;
				}
				break;
			case kAmmo:
				AudioManager::Get()->PlayAmmoPickup(GetPosition());
				GameManager::Get()->GetPlayer()->AddAmmo(m_Amount);
				m_bIsEaten = true;
				break;
			case kScore:
				AudioManager::Get()->PlayAmmoPickup(GetPosition());
				GameManager::Get()->GetPlayer()->AddScore(m_Amount);
				m_bIsEaten = true;
				break;
			}
		}
	}
}

void Pickup::Render()
{
	if (m_bIsEaten == false)
	{
		Item::Render();
	}
}