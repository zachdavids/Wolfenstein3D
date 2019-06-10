#include "Enemy.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "AABB.h"
#include "Player.h"
#include "Camera.h"
#include "Level.h"
#include "Ray.h"
#include "Collision.h"

#include <GLM/gtc/constants.hpp>
#include <GLM/glm.hpp>
#include <random>

const float STOP_DISTANCE = 3.0f;

const float WEAPON_RANGE = 100.0f;
const float WEAPON_ANGLE = 10.0f;
const float ATTACK_CHANCE = 0.5f;
const int DAMAGE_AMOUNT = 6;

const int Enemy::s_MaxHP = 100;
const float Enemy::s_MovementSpeed = 0.01f;
const float Enemy::s_SightRange = 5.0f;

Enemy::Enemy(glm::vec3 const& position)
{
	SetPosition(position);
	SetScale(glm::vec3(0.75f));
	
	m_CurrentHP = s_MaxHP;
	death_time_ = 0;
	hurt_time_ = 0;
	m_CurrentState = kIdle;
	dead_ = false;
	can_look_ = false;
	can_attack_ = false;

	m_Shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Billboard");
}

void Enemy::Idle()
{
	m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Idle");

	if (m_DistanceToPlayer < s_SightRange)
	{
		m_CurrentState = kChase;

		Ray ray;
		ray.m_Origin = GetPosition();
		ray.m_Direction = m_PlayerDirection;
		ray.m_InvDirection = 1.0f / m_PlayerDirection;

		if (Collision::RayAABBIntersection(ray, GameManager::Get()->GetPlayer()->GetAABB()))
		{

		}
			//glm::vec3 collision_vector = GameManager::Get()->GetLevel()->CheckIntersection(line_origin, line_end, false);
			//glm::vec3 player_position = GameManager::Get()->GetPlayer()->m_Transform.GetPosition();
			//glm::vec3 player_collision = GameManager::Get()->GetLevel()->LineIntersectionRectangle(line_origin, line_end, glm::vec3(player_position.x, 0, player_position.z), 0.2f, 0.2f);

			//if (player_collision != glm::vec3(NULL) && collision_vector == glm::vec3(NULL) ||
			//	glm::length(player_collision - line_origin) < glm::length(collision_vector - line_origin)) {
			//	state_ = CHASE_STATE;
			//}
	}
}

void Enemy::Chase()
{
	double time = TimeManager::GetTime() - (int)TimeManager::GetTime();

	if (m_DistanceToPlayer > STOP_DISTANCE) 
	{
		if (time < 0.25f) 
		{
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Walk1");
		}
		else if (time < 0.50f) 
		{
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Walk2");
		}
		else if (time < 0.75f) 
		{
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Walk3");
		}
		else if (time < 1.00f) 
		{
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Walk4");
		}

		glm::vec3 old_position = GetPosition();
		glm::vec3 new_position = GetPosition() + (m_PlayerDirection * s_MovementSpeed);
		glm::vec3 movement_vector = m_PlayerDirection;

		if (GameManager::Get()->GetLevel()->CheckAABBCollision(GetAABB()))
		{
			movement_vector = glm::vec3(0.0f);
		}

		if (glm::length(movement_vector) > 0)
		{
			SetPosition(GetPosition() + (movement_vector * s_MovementSpeed));
			//audio_->PlayStep();
		}
	}
	else 
	{
		m_CurrentState = kAttack;
	}
}

void Enemy::Attack()
{
	double time = TimeManager::GetTime() - (int)TimeManager::GetTime();

	if (time < 0.40f) 
	{
		can_attack_ = true;
		m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot1");
	}
	else if (time < 0.80f) 
	{
		m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot2");
	}
	else if (time < 1.00f) 
	{
		if (can_attack_) 
		{
			//audio_->PlayEnemyGunshot();
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot3");
			std::random_device generator;
			std::uniform_real_distribution<float> distribution(0.0f, 10.0f);
			float random = distribution(generator);

			glm::vec3 line_origin = GetPosition();
			glm::vec3 line_direction = m_PlayerDirection;
			glm::vec3 line_end = line_origin + (line_direction * 100.0f);

			//glm::vec3 collision_vector = GameManager::Get()->GetLevel()->CheckIntersection(line_origin, line_end, false);
			//glm::vec3 player_position = GameManager::Get()->GetPlayer()->m_Transform.GetPosition();
			//glm::vec3 player_collision = GameManager::Get()->GetLevel()->LineIntersectionRectangle(line_origin, line_end, glm::vec3(player_position.x, 0, player_position.z), 0.2f, 0.2f);

			//if (player_collision != glm::vec3(NULL) && collision_vector == glm::vec3(NULL) ||
			//	glm::length(player_collision - line_origin) < glm::length(collision_vector - line_origin)) {
			//	Player::Damage(DAMAGE_AMOUNT);
			//	
			//	state_ = CHASE_STATE;
			//}
			//can_attack_ = false;
		}
		else 
		{
			m_CurrentState = kChase;
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot1");
			can_attack_ = true;
		}
	}
}

AABB Enemy::GetAABB()
{
	AABB aabb;
	aabb.m_Min = glm::vec3(-0.1f, 0, -0.1) + GetPosition();;
	aabb.m_Max = glm::vec3(0.1f, 0, 0.1f) + GetPosition();;
	return aabb;
}

void Enemy::Damage(int damage_points)
{
	if (m_CurrentState = kIdle) 
	{
		m_CurrentState = kChase;
	}

	m_CurrentHP -= damage_points;

	if (m_CurrentHP > 0) 
	{
		m_CurrentState = kHurt;
	}
	else if (m_CurrentHP <= 0) 
	{
		//audio_->PlayEnemyDeath();
		m_CurrentState = kDeath;
	}
}

void Enemy::Hurt()
{
	m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Pain1");
	m_CurrentState = kAttack;
}

void Enemy::Death()
{
	m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Die4");
}

void Enemy::FaceCamera()
{
	float m_Cameraangle = -atanf(m_PlayerDirection.z/m_PlayerDirection.x) + (90.0f*glm::pi<float>() / 180.0f);

	if (m_PlayerDirection.x > 0) 
	{
		m_Cameraangle += glm::pi<float>();
	}

	SetRotation(glm::vec3(0, m_Cameraangle, 0));
}

void Enemy::Update()
{
	glm::vec3 player_position = GameManager::Get()->GetPlayer()->GetPosition();
	m_PlayerDirection = glm::normalize(player_position - GetPosition());
	m_DistanceToPlayer = glm::length(player_position - GetPosition());
	
	FaceCamera();

	switch(m_CurrentState)
	{
		case kIdle:
			Idle();
			break;
		case kChase:
			Chase();
			break;
		case kAttack:
			Attack();
			break;
		case kHurt:
			Hurt();
			break;
		case kDeath:
			Death();
			break;
	}
}

void Enemy::Render()
{
	m_Shader->Bind();
	m_Shader->SetMat4("model", GetModelMatrix());
	m_CurrentAnimation->Bind();
	m_Mesh->Draw();
}