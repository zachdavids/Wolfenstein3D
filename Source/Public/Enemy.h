#pragma once

#include "Transform.h"
#include "Player.h"
#include "AudioManager.h"

#include <GLM/glm.hpp>
#include <GLM/gtx/intersect.hpp>

#include <random>

class Texture;

class Enemy
{
public:

	Enemy() {};
	Enemy(glm::vec3 position);

	void Update();
	void Render();

	glm::vec2 GetSize();

	glm::vec3 GetTranslation() { return transform_->GetTranslation(); };
	void Damage(int damage_points);

private:

	int hp_;
	int hurt_time_;
	int death_time_;
	int state_;
	bool dead_;
	bool can_look_;
	bool can_attack_;

	glm::vec3 position_;

	Texture* m_CurrentAnimation;
	Transform* transform_;

	void Idle(glm::vec3 orientation, float distance);
	void Chase(glm::vec3 orientation, float distance);
	void Attack(glm::vec3 orientation, float distance);
	void Hurt(glm::vec3 orientation, float distance);

	void Death(glm::vec3 orientation, float distance);
	void FaceCamera(glm::vec3 orientation);
};