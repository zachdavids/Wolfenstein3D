#pragma once

#include "Actor.h"
#include "Camera.h"
#include "BoundingBox.h"
#include "HUD.h"
#include "Weapon.h"

#include <GLM/vec3.hpp>

#include <memory>

class Player : public Actor
{
public:

	Player(glm::vec3 const& position, glm::vec3 const& rotation);
	void Input();
	virtual void Update() override;
	virtual void Render() override;
	void Damage(int damage);
	void AddAmmo(int amount);
	void AddScore(int amount);
	void AddLife(int amount);
	void AddSubmachineGun();
	int GetHealth();
	int GetMaxHealth();
	int GetLives();
	int GetAmmo();
	int GetScore();
	Camera* GetCamera();
	BoundingBox GetBoundingBox();

private:

	int m_Lives;
	int m_Ammo;
	int m_CurrentWeapon;
	int m_CurrentHP;
	int m_Score;
	glm::vec3 m_Spawn;
	glm::vec3 m_Movement;
	HUD m_HUD;
	std::vector<Weapon> m_Weapons;
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
	void PlaySound();
	void Reset();
};