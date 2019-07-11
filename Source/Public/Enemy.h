#pragma once

#include "Actor.h"
#include "AABB.h"
#include "Weapon.h"

class Enemy : public Actor
{
public:

	enum State : int
	{
		kIdle,
		kChase,
		kAttack,
		kHurt,
		kDeath
	};

	Enemy(glm::vec3 const& position);
	virtual void Update() override;
	AABB GetAABB();
	void Damage(int damage_points);
	bool IsAlive();
	static constexpr int s_MaxHP = 100;
	static constexpr int s_Damage = 6;
	static constexpr float s_MovementSpeed = 0.01f;
	static constexpr float s_SightRange = 120.0f;
	static constexpr float s_AttackRange = 3.5f;

private:

	int m_CurrentHP;
	int m_CurrentState;
	bool m_bCanAttack;
	float m_DistanceToPlayer;
	glm::vec3 m_PlayerDirection;
	Weapon m_Weapon;
	bool CheckSightline();
	void Idle();
	void Chase();
	void Attack();
	void Hurt();
	void Death();
	void FaceCamera();
	void PlayWeaponAnimation(double last_fire);
	void Shoot();
};