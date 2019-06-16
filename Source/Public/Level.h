#pragma once

#include "Door.h"
#include "Enemy.h"
#include "Item.h"
#include "Wall.h"
#include "Ray.h"
#include "Pickup.h"

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <vector>

class Player;

class Level
{
public:

	Level() = default;
	Level(std::string const& filename);
	void Input();
	void Update();
	void Render();
	void OpenDoors(glm::vec3 const& position, bool exit);
	bool CheckPlayerRayCollision(Ray& ray);
	bool CheckEnemyRayCollision(Ray& ray);
	bool CheckAABBCollision(AABB& actor, glm::vec3& normal, glm::vec3& position);

private:

	Player* m_Player;
	Shader* m_TextShader; //temp
	Shader* m_DefaultShader; //temp
	Shader* m_TileShader; //temp
	std::vector<Wall> m_LevelGeometry;
	std::vector<AABB> m_StaticGeometry;
	std::vector<Door> m_Doors;
	std::vector<Enemy> m_Enemies;
	std::vector<Item> m_Items;
	std::vector<Pickup> m_Pickups;
	glm::vec3 m_Endpoint;
	glm::ivec2 m_LevelDimensions;
	void GenerateLevel(std::string const& file_name);
	int FlatIndex(int x, int y);
	bool ClosestCollision(Ray& ray, Actor* actor);
	bool CompareLengths(glm::vec3 const& length_one, glm::vec3 const& length_two);
};