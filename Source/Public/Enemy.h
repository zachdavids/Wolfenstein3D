#pragma once

#include "Mesh.h"
#include "Transform.h"
#include "Player.h"
#include "Audio.h"

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
	Mesh mesh_;
	Transform* transform_;
	Audio* audio_;

	void Idle(glm::vec3 orientation, float distance);
	void Chase(glm::vec3 orientation, float distance);
	void Attack(glm::vec3 orientation, float distance);
	void Hurt(glm::vec3 orientation, float distance);

	void Death(glm::vec3 orientation, float distance);
	void FaceCamera(glm::vec3 orientation);

	void AddIndices(std::vector<unsigned int>& indices, int start, bool direction);
	void AddVertices(std::vector<Vertex>& vertices, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords);
	std::vector<float> CalculateTextureCoords(int texture_number);
};