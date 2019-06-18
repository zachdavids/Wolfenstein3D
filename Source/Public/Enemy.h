#pragma once

#include "Actor.h"
#include "AABB.h"
#include "Weapon.h"

class TextureArray;
class Mesh;
class Shader;

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
	virtual void Render() override;
	AABB GetAABB();
	void Damage(int damage_points);
	bool IsAlive();

private:

	int m_Tid = 14;
	int m_CurrentHP;
	int m_CurrentState;
	bool m_bCanAttack;
	float m_DistanceToPlayer;
	glm::vec3 m_PlayerDirection;
	static const int s_MaxHP;
	static const int s_Damage;
	static const float s_MovementSpeed;
	static const float s_SightRange;
	static const float s_AttackRange;
	Weapon m_Weapon;
	TextureArray* m_Texture;
	Mesh* m_Mesh;
	Shader* m_Shader;
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