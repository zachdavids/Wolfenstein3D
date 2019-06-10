#pragma once

#include "Door.h"
#include "Enemy.h"
#include "Medkit.h"
#include "Wall.h"
#include "Ray.h"

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <vector>

class Player;

class Level
{
public:

	Level(std::string const& filename);
	void Input();
	void Update();
	void Render();
	void OpenDoors(glm::vec3& position, bool exit);
	bool CheckPlayerRayCollision(Ray& ray);
	bool CheckEnemyRayCollision(Ray& ray);
	bool CheckAABBCollision(AABB& one);

private:

	Player* m_Player;
	Shader* m_TextShader; //temp
	Shader* m_DefaultShader; //temp
	std::vector<Wall> m_LevelGeometry;
	std::vector<AABB> m_CollisionGeometry;
	std::vector<Door> m_Doors;
	std::vector<Enemy> m_Enemies;
	std::vector<Medkit> m_Medkits;
	glm::vec3 m_Endpoint;
	glm::vec2 m_LevelDimensions;
	void GenerateLevel(std::string const& file_name);
	int FlatIndex(int x, int y);
	void RemoveMedkit();
};