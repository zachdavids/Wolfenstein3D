#pragma once

#include "Player.h"
#include "Door.h"
#include "Enemy.h"
#include "Medkit.h"
#include "Wall.h"
#include "Ray.h"

#include <GLM/vec3.hpp>
#include <vector>

class Level
{
public:

	Level(std::string filename);

	void Input();
	void Update();
	void Render();
	void OpenDoors(glm::vec3 position, bool exit);
	bool CheckRayCollision(Ray& ray);
	bool CheckAABBCollision(AABB& one);

private:

	Player* m_Player;
	Camera* camera_;
	Enemy* enemy_;

	Shader* m_TextShader; //temp
	Shader* m_DefaultShader; //temp

	std::vector<Wall> m_LevelGeometry;
	std::vector<AABB> m_CollisionGeometry;
	std::vector<Door> doors_;
	std::vector<Enemy> enemies_;
	std::vector<Medkit> medkits_;
	std::vector<glm::vec3> endpoints_;

	void GenerateLevel(std::string const& file_name);
	void RemoveMedkit();
};