#include "Player.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "AudioManager.h"
#include "TextureArray.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Level.h"
#include "Ray.h"

#include <GLFW/glfw3.h>
#include <GLM/geometric.hpp>
#include <GLM/gtc/constants.hpp>

const int Player::s_MaxHP = 100;
const float Player::s_MovementSpeed = 0.05f;
const float Player::s_LookSensitivity = 0.001f;

Player::Player(glm::vec3 const& position, glm::vec3 const& rotation) :
	Actor(
		position,
		rotation,
		78,
		ResourceManager::Get()->GetResource<Mesh>("Billboard"),
		ResourceManager::Get()->GetResource<Shader>("TileShader"),
		ResourceManager::Get()->GetResource<TextureArray>("SpriteSheet")
	),
	m_CurrentHP(s_MaxHP),
	m_CurrentWeapon(1),
	m_Ammo(8),
	m_Lives(3),
	m_Score(0),
	m_Spawn(position)
{
	m_Weapons = {
		Weapon{ true, 1.5f, 0.15f, 0 },
		Weapon{ true, 100.0f, 0.15f, 0 },
		Weapon{ true, 100.0f, 0.10f, 0 },
		Weapon{ true, 100.0f, 0.05f, 0 } 
	};

	m_Camera = std::make_unique<Camera>(position, rotation);
}

void Player::Input()
{
	MouseInput();
	KeyboardInput();
}

void Player::Update()
{
	if (m_Weapons[m_CurrentWeapon].bFireable == false)
	{
		double last_fire = TimeManager::GetTime() - m_Weapons[m_CurrentWeapon].last_interval;
		if (last_fire > m_Weapons[m_CurrentWeapon].rate)
		{
			m_Weapons[m_CurrentWeapon].bFireable = true;
		}
		else
		{
			PlayWeaponAnimation(last_fire);
		}
	}

	glm::vec3 intention = m_Movement * s_MovementSpeed;
	glm::vec3 new_position = m_Camera->GetPosition() + intention;
	AABB aabb{ new_position, glm::vec3(0.1f, 0, 0.1) };

	glm::vec3 collision(1.0f);
	glm::vec3 delta(0.0f);
	GameManager::Get()->GetLevel()->CheckAABBCollision(aabb, collision, delta);
	Move((intention + delta) * collision);
}

void Player::Render()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	m_Shader->Bind();
	m_Shader->SetMat4("model", GetModelMatrix());
	m_Shader->SetInt("index", m_Tid);
	m_Texture->Bind();
	m_Mesh->Draw();
	m_HUD.Render();
	glEnable(GL_DEPTH_TEST);
}

void Player::MouseInput()
{
	double mouse_x;
	double mouse_y;
	glfwGetCursorPos(WindowManager::Get()->GetWindow(), &mouse_x, &mouse_y);

	double window_width = (double)WindowManager::Get()->s_Width;
	double window_height = (double)WindowManager::Get()->s_Height;

	if (mouse_x != window_width / 2.0)
	{
		m_Camera->Aim((float)(mouse_x - window_width/2.0) * s_LookSensitivity);
	}

	glfwSetCursorPos(WindowManager::Get()->GetWindow(), window_width / 2.0f, window_height / 2.0f);
}

void Player::KeyboardInput()
{
	m_Movement = glm::vec3(0.0f);
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_1))
	{
		ChangeWeapon(0);
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_2))
	{
		if (m_Ammo > 0)
		{
			ChangeWeapon(1);
		}
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_3))
	{
		if (m_Ammo > 0)
		{
			ChangeWeapon(2);
		}
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_4))
	{
		if (m_Ammo > 0)
		{
			ChangeWeapon(3);
		}
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_A))
	{
		m_Movement -= m_Camera->GetRight();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_D))
	{
		m_Movement += m_Camera->GetRight();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_W))
	{
		m_Movement += m_Camera->GetForward();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_S))
	{
		m_Movement -= m_Camera->GetForward();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_E))
	{
		GameManager::Get()->GetLevel()->OpenDoors(GetPosition(), true);
	}
	if (glfwGetMouseButton(WindowManager::Get()->GetWindow(), GLFW_MOUSE_BUTTON_LEFT))
	{
		Shoot();
	}
}

void Player::PlayWeaponAnimation(double last_fire)
{
	int num_animations = 5;
	double time_per_animation = m_Weapons[m_CurrentWeapon].rate / num_animations;
	m_Tid = 79 - (m_CurrentWeapon * num_animations) + (int)glm::floor(last_fire / time_per_animation);
}

void Player::Move(glm::vec3 const& movement)
{
	m_Camera->Move(movement);
	SetPosition(glm::vec3(m_Camera->GetPosition().x + m_Camera->GetForward().x, 0.0f, m_Camera->GetPosition().z + m_Camera->GetForward().z));
	glm::vec3 camera_direction(m_Camera->GetPosition().x - GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z - GetPosition().z);
	float camera_angle = -atanf(camera_direction.z / camera_direction.x) + (90.0f * glm::pi<float>() / 180.0f);

	if (camera_direction.x > 0)
	{
		camera_angle += glm::pi<float>();
	}
	SetRotation(glm::vec3(0, camera_angle, 0));
	AudioManager::Get()->SetListenerPosition(m_Camera->GetPosition(), GetRotation());
}

void Player::ChangeWeapon(int weapon)
{
	m_CurrentWeapon = weapon;
	m_HUD.UpdateWeapon(weapon);
	m_Tid = 83 - (m_CurrentWeapon * 5);
}

void Player::PlaySound()
{
	switch (m_CurrentWeapon)
	{
	case 0:
		AudioManager::Get()->PlayKnife(GetPosition());
		break;
	case 1:
		AudioManager::Get()->PlayPistol(GetPosition());
		break;
	case 2:
		AudioManager::Get()->PlayMachineGun(GetPosition());
		break;
	case 3:
		AudioManager::Get()->PlayMinigun(GetPosition());
		break;
	}
}

void Player::Reset()
{
	m_Ammo = 8;
	m_CurrentHP = 100;
	ChangeWeapon(2);
	GameManager::Get()->ResetGame();
}

void Player::Shoot()
{
	if (m_Weapons[m_CurrentWeapon].bFireable)
	{
		PlaySound();

		Ray ray;
		ray.m_Origin = glm::vec3(m_Camera->GetPosition().x, 0, m_Camera->GetPosition().z);
		ray.m_Direction = glm::normalize(glm::vec3(m_Camera->GetForward().x, 0, m_Camera->GetForward().z));
		ray.m_InvDirection = 1.0f / ray.m_Direction;
		GameManager::Get()->GetLevel()->CheckPlayerRayCollision(ray, m_Weapons[m_CurrentWeapon].range);
		m_Weapons[m_CurrentWeapon].bFireable = false;
		m_Weapons[m_CurrentWeapon].last_interval = TimeManager::GetTime();

		if (m_Ammo > 0 && m_CurrentWeapon != 0) 
		{
			--m_Ammo;
		}
		else 
		{
			ChangeWeapon(0);
		}
	}
}

void Player::Damage(int damage)
{
	m_CurrentHP -= damage;

	if (m_CurrentHP <= 0)
	{
		if (m_Lives > 0)
		{
			--m_Lives;
			Reset();
		}
		else
		{
			exit(0);
		}
	}
	else if (m_CurrentHP > s_MaxHP)
	{
		m_CurrentHP = s_MaxHP;
	}
}

int Player::GetHealth()
{
	return m_CurrentHP;
}

int Player::GetMaxHealth()
{
	return s_MaxHP;
}

int Player::GetLives()
{
	return m_Lives;
}

int Player::GetAmmo()
{
	return m_Ammo;
}

int Player::GetScore()
{
	return m_Score;
}

void Player::AddAmmo(int amount)
{
	m_Ammo += amount;
}

void Player::AddScore(int amount)
{
	m_Score += amount;
}

Camera* Player::GetCamera()
{
	return m_Camera.get();
}

AABB Player::GetAABB()
{
	return AABB{ m_Camera->GetPosition(), glm::vec3(0.1f, 0, 0.1f) };
}
