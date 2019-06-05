#pragma once

#include "Actor.h"

class Texture;
class Mesh;
class Shader;

class Enemy : public Actor
{
public:

	Enemy(glm::vec3 position);

	virtual void Update() override;
	virtual void Render() override;

	glm::vec2 GetSize();

	glm::vec3 GetTranslation() { return m_Transform.GetPosition(); };
	void Damage(int damage_points);

private:

	int hp_;
	int hurt_time_;
	int death_time_;
	int state_;
	bool dead_;
	bool can_look_;
	bool can_attack_;

	Texture* m_CurrentAnimation;
	Mesh* m_Mesh;
	Shader* m_Shader;

	void Idle(glm::vec3 orientation, float distance);
	void Chase(glm::vec3 orientation, float distance);
	void Attack(glm::vec3 orientation, float distance);
	void Hurt(glm::vec3 orientation, float distance);

	void Death(glm::vec3 orientation, float distance);
	void FaceCamera(glm::vec3 orientation);
};