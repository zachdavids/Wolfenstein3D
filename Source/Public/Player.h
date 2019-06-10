#pragma once

#include "Actor.h"
#include "Camera.h"
#include "AABB.h"
#include "HUD.h"

#include <memory>
#include <GLM/vec3.hpp>

class Texture;
class Mesh;
class Camera;
class TextShader;
class Shader;

struct FireRate
{
	bool bFireable;
	float rate;
	float last_interval;
};

class Player : public Actor
{
public:

	Player(glm::vec3 const& position, glm::vec3 const& rotation);
	void Input();
	void Update();
	void Render();
	void Damage(int damage);
	int GetHealth();
	Camera* GetCamera();
	AABB GetAABB();

private:

	bool shot_;
	int m_CurrentHP;
	static const int s_MaxHP;
	static const float s_MovementSpeed;
	static const float s_LookSensitivity;
	static const float s_RateOfFire;
	glm::vec3 m_Movement;
	FireRate m_FireRate;
	HUD m_HUD;
	Mesh* m_Mesh = nullptr;
	Shader* m_DefaultShader = nullptr;
	Texture* m_CurrentAnimation = nullptr;
	std::unique_ptr<Camera> m_Camera;
	void Shoot();
	void MouseInput();
	void KeyboardInput();
};