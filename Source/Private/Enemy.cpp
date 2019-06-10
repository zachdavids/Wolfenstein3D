#include "Enemy.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Player.h"
#include "AudioManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Camera.h"
#include "Level.h"
#include "TimeManager.h"
#include "AABB.h"

#include <GLM/gtc/constants.hpp>
#include <GLM/glm.hpp>
#include <random>

const float BODY_WIDTH = 0.2f;
const float BODY_LENGTH = 0.2f;
const float MOVEMENT_SPEED = 0.01f;
const float STOP_DISTANCE = 3.0f;

const float WEAPON_RANGE = 100.0f;
const float WEAPON_ANGLE = 10.0f;
const float ATTACK_CHANCE = 0.5f;
const int DAMAGE_AMOUNT = 6;

const int IDLE_STATE = 0;
const int CHASE_STATE = 1;
const int ATTACK_STATE = 2;
const int HURT_STATE = 3;
const int DEATH_STATE = 4;

const int HIT_POINTS = 100;

Enemy::Enemy(glm::vec3 position)
{
	m_Transform.SetPosition(position);
	m_Transform.SetScale(glm::vec3(0.75f));

	hp_ = HIT_POINTS;
	death_time_ = 0;
	hurt_time_ = 0;
	state_ = IDLE_STATE;
	dead_ = false;
	can_look_ = false;
	can_attack_ = false;

	m_Shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_Shader->SetMat4("model", m_Transform.GetModelMatrix());
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Billboard");
}

void Enemy::Idle(glm::vec3 orientation, float distance)
{
	m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Idle");

	glm::vec3 line_origin = m_Transform.GetPosition();
	glm::vec3 line_direction = orientation;
	glm::vec3 line_end = line_origin + (line_direction * 100.0f);

	//glm::vec3 collision_vector = GameManager::Get()->GetLevel()->CheckIntersection(line_origin, line_end, false);
	//glm::vec3 player_position = GameManager::Get()->GetPlayer()->m_Transform.GetPosition();
	//glm::vec3 player_collision = GameManager::Get()->GetLevel()->LineIntersectionRectangle(line_origin, line_end, glm::vec3(player_position.x, 0, player_position.z), 0.2f, 0.2f);

	//if (player_collision != glm::vec3(NULL) && collision_vector == glm::vec3(NULL) ||
	//	glm::length(player_collision - line_origin) < glm::length(collision_vector - line_origin)) {
	//	state_ = CHASE_STATE;
	//}
}

void Enemy::Chase(glm::vec3 orientation, float distance)
{
	double time = TimeManager::GetTime() - (int)TimeManager::GetTime();

	if (distance > STOP_DISTANCE) {
		if (time < 0.25f) {
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Walk1");
		}
		else if (time < 0.50f) {
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Walk2");
		}
		else if (time < 0.75f) {
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Walk3");
		}
		else if (time < 1.00f) {
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Walk4");
		}

		glm::vec3 old_position = m_Transform.GetPosition();
		glm::vec3 new_position = m_Transform.GetPosition() + (orientation * MOVEMENT_SPEED);
		glm::vec3 movement_vector = orientation;

		if (GameManager::Get()->GetLevel()->CheckAABBCollision(GetAABB()))
		{
			movement_vector = glm::vec3(0.0f);
		}

		if (glm::length(movement_vector) > 0) {
			m_Transform.SetPosition(m_Transform.GetPosition() + (movement_vector * MOVEMENT_SPEED));
			//audio_->PlayStep();
		}
	}
	else {
		state_ = ATTACK_STATE;
	}
}

void Enemy::Attack(glm::vec3 orientation, float distance)
{
	double time = TimeManager::GetTime() - (int)TimeManager::GetTime();

	if (time < 0.40f) {
		can_attack_ = true;
		m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot1");
	}
	else if (time < 0.80f) {
		m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot2");
	}
	else if (time < 1.00f) {
		if (can_attack_) {
			//audio_->PlayEnemyGunshot();
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot3");
			std::random_device generator;
			std::uniform_real_distribution<float> distribution(0.0f, 10.0f);
			float random = distribution(generator);

			glm::vec3 line_origin = m_Transform.GetPosition();
			glm::vec3 line_direction = orientation;
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
		else {
			state_ = CHASE_STATE;
			m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Shoot1");
			can_attack_ = true;
		}
	}
}

AABB Enemy::GetAABB()
{
	AABB aabb;
	aabb.m_Min = glm::vec3(-0.1f, 0, -0.1) + m_Transform.GetPosition();;
	aabb.m_Max = glm::vec3(0.1f, 0, 0.1f) + m_Transform.GetPosition();;
	return aabb;
}

void Enemy::Damage(int damage_points)
{
	if (state_ = IDLE_STATE) {
		state_ = CHASE_STATE;
	}

	hp_ -= damage_points;

	if (hp_ > 0) {
		state_ = HURT_STATE;
	}
	else if (hp_ <= 0) {
		//audio_->PlayEnemyDeath();
		state_ = DEATH_STATE;
	}
}

void Enemy::Hurt(glm::vec3 orientation, float distance)
{
	m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Pain1");

	state_ = ATTACK_STATE;
}

void Enemy::Death(glm::vec3 orientation, float distance)
{
	m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Guard_Die4");
}

void Enemy::FaceCamera(glm::vec3 orientation)
{
	float m_Cameraangle = -atanf(orientation.z / orientation.x) + (90.0f * glm::pi<float>() / 180.0f);

	if (orientation.x > 0) {
		m_Cameraangle += glm::pi<float>();
	}

	m_Transform.SetRotation(0, m_Cameraangle, 0);
}

void Enemy::Update()
{
	glm::vec3 player_position = GameManager::Get()->GetPlayer()->m_Transform.GetPosition();
	glm::vec3 camera_direction(player_position.x - m_Transform.GetPosition().x, 0, player_position.z - m_Transform.GetPosition().z);
	float camera_distance = glm::length(camera_direction);

	glm::vec3 camera_orientation = camera_direction / camera_distance;
	
	FaceCamera(camera_orientation);

	switch(state_) {
		case IDLE_STATE:
			Idle(camera_orientation, camera_distance);
			break;
		case CHASE_STATE:
			Chase(camera_orientation, camera_distance);
			break;
		case ATTACK_STATE:
			Attack(camera_orientation, camera_distance);
			break;
		case HURT_STATE:
			Hurt(camera_orientation, camera_distance);
			break;
		case DEATH_STATE:
			Death(camera_orientation, camera_distance);
			break;
	}
}

void Enemy::Render()
{
	m_Shader->Bind();
	m_Shader->SetMat4("model", m_Transform.GetModelMatrix());
	m_CurrentAnimation->Bind();
	m_Mesh->Draw();
}

glm::vec2 Enemy::GetSize()
{
	return glm::vec2(BODY_WIDTH, BODY_LENGTH);
}