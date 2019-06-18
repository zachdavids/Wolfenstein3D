#pragma once

#include "Actor.h"
#include "Camera.h"
#include "AABB.h"
#include "HUD.h"
#include "Weapon.h"

#include <memory>
#include <GLM/vec3.hpp>

class TextureArray;
class Mesh;
class Camera;
class TextShader;
class Shader;

class Player : public Actor
{
public:

	Player(glm::vec3 const& position, glm::vec3 const& rotation);
	void Input();
	void Update();
	void Render();
	void Damage(int damage);
	int GetHealth();
	int GetMaxHealth();
	int GetLives();
	int GetAmmo();
	int GetScore();
	void AddAmmo(int amount);
	void AddScore(int amount);
	Camera* GetCamera();
	AABB GetAABB();

private:

	bool shot_;
	int m_Lives;
	int m_Ammo;
	int m_CurrentWeapon;
	int m_CurrentHP;
	int m_Tid = 78;
	int m_Score;
	glm::vec3 m_Spawn;
	glm::vec3 m_Movement;
	HUD m_HUD;
	std::vector<Weapon> m_Weapons;
	Mesh* m_Mesh = nullptr;
	Shader* m_TileShader = nullptr;
	TextureArray* m_Texture = nullptr;
	std::unique_ptr<Camera> m_Camera;
	static const int s_MaxHP;
	static const float s_MovementSpeed;
	static const float s_LookSensitivity;

	void Shoot();
	void MouseInput();
	void KeyboardInput();
	void PlayWeaponAnimation(double last_fire);
	void Move(glm::vec3 const& movement);
	void ChangeWeapon(int weapon);
	void Reset();
};