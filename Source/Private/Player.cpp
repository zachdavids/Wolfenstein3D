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

#include <iostream>
#include <GLFW/glfw3.h>
#include <GLM/geometric.hpp>
#include <GLM/gtc/constants.hpp>

const int Player::s_MaxHP = 100;
const float Player::s_MovementSpeed = 0.08f;
const float Player::s_LookSensitivity = 0.001f;

Player::Player(glm::vec3 const& position, glm::vec3 const& rotation) :
	m_CurrentHP(s_MaxHP),
	m_Movement(glm::vec3(0.0f)),
	shot_(false),
	m_FireRate{ true, 0.15f, 0.0f },
	m_CurrentWeapon(2)
{
	SetPosition(position);
	SetRotation(rotation);
	//SetScale(glm::vec3(0.5f));

	m_Camera = std::make_unique<Camera>(position, rotation);
	m_TileShader = ResourceManager::Get()->GetResource<Shader>("TileShader");
	m_Texture = ResourceManager::Get()->GetResource<TextureArray>("SpriteSheet");
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Billboard");
}

void Player::Input()
{
	MouseInput();
	KeyboardInput();
}

void Player::Update()
{
	if (m_FireRate.bFireable == false)
	{
		double last_fire = TimeManager::GetTime() - m_FireRate.last_interval;
		if (last_fire > m_FireRate.rate)
		{
			m_FireRate.bFireable = true;
		}
		else
		{
			PlayWeaponAnimation(last_fire);
		}
	}

	glm::vec3 intention = m_Movement * s_MovementSpeed;
	glm::vec3 collision = glm::vec3(1.0f);
	glm::vec3 new_position = m_Camera->GetPosition() + intention;
	AABB aabb;
	aabb.m_Min = glm::vec3(-0.1f, 0, -0.1f) + new_position;
	aabb.m_Max = glm::vec3(0.1f, 0, 0.1f) + new_position;
	aabb.m_Position = new_position;

	if (GameManager::Get()->GetLevel()->CheckAABBCollision(aabb) == false)
	{
		m_Camera->Move(m_Movement * collision * s_MovementSpeed);
	}

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

void Player::Render()
{
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	m_TileShader->Bind();
	m_TileShader->SetMat4("model", GetModelMatrix());
	m_TileShader->SetInt("index", m_Tid);
	m_Texture->Bind();
	m_Mesh->Draw();
	m_HUD.Render();
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}

void Player::MouseInput()
{
	double mouse_x;
	double mouse_y;
	glfwGetCursorPos(WindowManager::Get()->GetWindow(), &mouse_x, &mouse_y);

	double window_width = (double)WindowManager::Get()->GetWidth();
	double window_height = (double)WindowManager::Get()->GetHeight();

	if (mouse_x != window_width / 2.0)
	{
		m_Camera->Aim((float)(mouse_x - window_width/2.0) * s_LookSensitivity);
	}

	glfwSetCursorPos(WindowManager::Get()->GetWindow(), window_width / 2.0f, window_height / 2.0f);
}

void Player::KeyboardInput()
{
	m_Movement = glm::vec3(0.0f);
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
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_ESCAPE))
	{
		exit(1);
	}
}

//Play animation smoothed over fire rate
void Player::PlayWeaponAnimation(double last_fire)
{
	int num_animations = 5;
	float time_per_animation = m_FireRate.rate / num_animations;
	m_Tid = 70 - m_CurrentWeapon * num_animations + glm::floor(last_fire / time_per_animation);
}

void Player::Shoot()
{
	if (m_FireRate.bFireable)
	{
		shot_ = true;
		AudioManager::Get()->PlayPistol(GetPosition());

		Ray ray;
		ray.m_Origin = glm::vec3(m_Camera->GetPosition().x, 0, m_Camera->GetPosition().z);
		ray.m_Direction = glm::normalize(glm::vec3(m_Camera->GetForward().x, 0, m_Camera->GetForward().z));
		ray.m_InvDirection = 1.0f / ray.m_Direction;
		GameManager::Get()->GetLevel()->CheckPlayerRayCollision(ray);
		m_FireRate.bFireable = false;
		m_FireRate.last_interval = TimeManager::GetTime();
	}
}

void Player::Damage(int damage)
{
	m_CurrentHP -= damage;

	if (m_CurrentHP <= 0)
	{
		//Game::GameOver();
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

Camera* Player::GetCamera()
{
	return m_Camera.get();
}

AABB Player::GetAABB()
{
	AABB aabb;
	aabb.m_Min = glm::vec3(-0.1f, 0, -0.1f) + m_Camera->GetPosition();;
	aabb.m_Max = glm::vec3(0.1f, 0, 0.1f) + m_Camera->GetPosition();;
	aabb.m_Position = m_Camera->GetPosition();
	return aabb;
}
