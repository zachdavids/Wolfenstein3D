#include "Enemy.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "BoundingBox.h"
#include "Player.h"
#include "Level.h"
#include "Ray.h"

#include <GLM/geometric.hpp>
#include <GLM/gtc/constants.hpp>

#include <iostream>

Enemy::Enemy(glm::vec3 const& position) :
	m_CurrentHP(s_MaxHP),
	m_CurrentState(kIdle),
	m_bCanAttack(false)
{
	m_Position = position;
	m_Scale = glm::vec3(0.75f);
	m_Tid = 14;
	m_Weapon = Weapon{ true, 100.0f, 0.5f, 0 };
	m_Shader = ResourceManager::Get()->GetResource<Shader>("TileShader");
	m_Texture = ResourceManager::Get()->GetResource<TextureArray>("SpriteSheet");
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

void Enemy::Idle()
{
	m_Tid = 10;

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
			m_Tid = 3;
		}
		else if (time < 0.50f)
		{
			m_Tid = 2;
		}
		else if (time < 0.75f)
		{
			m_Tid = 1;
		}
		else if (time < 1.00f)
		{
			m_Tid = 0;
		}

		glm::vec3 collision(1.0f);
		glm::vec3 delta(0.0f);
		GameManager::Get()->GetLevel()->CheckBoundingBoxCollision(GetBoundingBox(), collision, delta);
		SetPosition(GetPosition() + (m_PlayerDirection * collision * s_MovementSpeed));
	}
}

void Enemy::Attack()
{
	if (m_Weapon.bFireable == false)
	{
		double last_fire = TimeManager::GetTime() - m_Weapon.last_interval;
		if (last_fire > m_Weapon.rate)
		{
			m_Weapon.bFireable = true;
		}
		else
		{
			PlayWeaponAnimation(last_fire);
		}
	}
	else
	{
		if (CheckSightline())
		{
			Shoot();
		}
		else
		{
			m_CurrentState = kChase;
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
		AudioManager::Get()->PlayEnemyDeath(m_Position);
		GameManager::Get()->GetLevel()->SpawnAmmo(m_Position);
		m_CurrentState = kDeath;
	}
}

bool Enemy::IsAlive()
{
	return m_CurrentState != kDeath;
}

void Enemy::Hurt()
{
	m_Tid = 8;
	m_CurrentState = kAttack;
}

void Enemy::Death()
{
	m_Tid = 10;
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

void Enemy::PlayWeaponAnimation(double last_fire)
{
	int num_animations = 3;
	double time_per_animation = m_Weapon.rate / num_animations;
	m_Tid = 6 - (int)glm::floor(last_fire / time_per_animation);
}

void Enemy::Shoot()
{
	AudioManager::Get()->PlayPistol(GetPosition());
	GameManager::Get()->GetPlayer()->Damage(s_Damage);
	m_Weapon.bFireable = false;
	m_Weapon.last_interval = TimeManager::GetTime();
}

bool Enemy::CheckSightline()
{
	Ray ray;
	ray.m_Origin = GetPosition();
	ray.m_Direction = m_PlayerDirection;
	ray.m_InvDirection = 1.0f / m_PlayerDirection;

	return GameManager::Get()->GetLevel()->CheckEnemyRayCollision(ray);
}

BoundingBox Enemy::GetBoundingBox()
{
	return BoundingBox{ GetPosition(), glm::vec3(0.1f, 0, 0.1f) };
}