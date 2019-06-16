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
			std::cout << glm::length(camera_direction) << std::endl;
			switch (m_Type)
			{
			case kHeal:
				AudioManager::Get()->PlayMedkit();
				GameManager::Get()->GetPlayer()->Damage(-m_Amount);
				break;
			}
			m_bIsEaten = true;
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