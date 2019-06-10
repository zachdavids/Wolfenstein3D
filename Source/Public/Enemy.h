#pragma once

#include "Actor.h"
#include "AABB.h"

class Texture;
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

private:

	int m_CurrentHP;
	int hurt_time_;
	int death_time_;
	int m_CurrentState;
	bool dead_;
	bool can_look_;
	bool can_attack_;

	static const int s_MaxHP;
	static const float s_MovementSpeed;
	static const float s_SightRange;

	glm::vec3 m_PlayerDirection;
	float m_DistanceToPlayer;

	Texture* m_CurrentAnimation;
	Mesh* m_Mesh;
	Shader* m_Shader;

	void Idle();
	void Chase();
	void Attack();
	void Hurt();
	void Death();
	void FaceCamera();
};