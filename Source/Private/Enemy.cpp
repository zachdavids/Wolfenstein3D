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
#include "Level.h"
#include "Ray.h"

#include <iostream>
#include <GLM/geometric.hpp>
#include <GLM/gtc/constants.hpp>

const int Enemy::s_MaxHP = 100;
const int Enemy::s_Damage = 6;
const float Enemy::s_MovementSpeed = 0.01f;
const float Enemy::s_SightRange = 150.0f;
const float Enemy::s_AttackRange = 3.0f;

Enemy::Enemy(glm::vec3 const& position) :
	m_CurrentHP(s_MaxHP),
	m_CurrentState(kIdle),
	m_bCanAttack(false)
{
	SetPosition(position);
	SetScale(glm::vec3(0.75f));

	m_Shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Billboard");
}

void Enemy::Update()
{
	glm::vec3 player_position = GameManager::Get()->GetPlayer()->GetCamera()->GetPosition();
	player_position.y = 0;
	m_PlayerDirection = glm::normalize(player_position - GetPosition());
	m_DistanceToPlayer = glm::length(player_position - GetPosition());

	FaceCamera();

	switch (m_CurrentState)
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

void Enemy::Idle()
{
	m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Idle");

	if (m_DistanceToPlayer < s_SightRange)
	{
		if (CheckSightline())
		{
			m_CurrentState = kChase;
		}
	}
}

void Enemy::Chase()
{
	double time = TimeManager::GetTime() - (int)TimeManager::GetTime();

	if (m_DistanceToPlayer < s_AttackRange) 
	{
		m_CurrentState = kAttack;
	}
	else 
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

		glm::vec3 collision(1.0f);
		glm::vec3 delta(0.0f);
		GameManager::Get()->GetLevel()->CheckAABBCollision(GetAABB(), collision, delta);
		SetPosition(GetPosition() + (m_PlayerDirection * collision * s_MovementSpeed));
	}
}

void Enemy::Attack()
{
	double time = TimeManager::GetTime() - (int)TimeManager::GetTime();

	if (time < 0.40f) 
	{
		m_bCanAttack = true;
		m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot1");
	}
	else if (time < 0.80f) 
	{
		m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot2");
	}
	else if (time < 1.00f) 
	{
		if (m_bCanAttack && CheckSightline())
		{
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot3");
			AudioManager::Get()->PlayPistol(GetPosition());
			m_bCanAttack = false;
		}
		else 
		{
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot1");
			m_CurrentState = kChase;
			m_bCanAttack = true;
		}
	}
}

void Enemy::Damage(int damage)
{
	m_CurrentHP -= damage;

	if (m_CurrentHP > 0) 
	{
		m_CurrentState = kHurt;
	}
	else
	{
		AudioManager::Get()->PlayEnemyDeath(GetPosition());
		m_CurrentState = kDeath;
	}
}

bool Enemy::IsAlive()
{
	return m_CurrentState != kDeath;
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
	float camera_angle = -atanf(m_PlayerDirection.z/m_PlayerDirection.x) + (90.0f*glm::pi<float>() / 180.0f);

	if (m_PlayerDirection.x > 0) 
	{
		camera_angle += glm::pi<float>();
	}

	SetRotation(glm::vec3(0, camera_angle, 0));
}

bool Enemy::CheckSightline()
{
	Ray ray;
	ray.m_Origin = GetPosition();
	ray.m_Direction = m_PlayerDirection;
	ray.m_InvDirection = 1.0f / m_PlayerDirection;

	return GameManager::Get()->GetLevel()->CheckEnemyRayCollision(ray);
}

AABB Enemy::GetAABB()
{
	return AABB{ GetPosition(), glm::vec3(0.1f, 0, 0.1f) };
}