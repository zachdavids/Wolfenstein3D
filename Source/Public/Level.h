#pragma once

#include "Door.h"
#include "Enemy.h"
#include "Item.h"
#include "Tile.h"
#include "Ray.h"
#include "Pickup.h"
#include "HiddenDoor.h"
#include "Elevator.h"

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <vector>
#include <string>

class Player;

class Level
{
public:

	Level(std::string const& filename);
	void Input();
	void Update();
	void Render();
	void OpenDoors(glm::vec3 const& position);
	bool CheckPlayerRayCollision(Ray& ray, float range);
	bool CheckEnemyRayCollision(Ray& ray);
	bool CheckAABBCollision(AABB actor, glm::vec3 normal, glm::vec3 position);
	void GenerateLevel(std::string const& file_name);
	void SpawnAmmo(glm::vec3 const& position);
	int GetLevelNumber();
	glm::vec3 GetSpawnPoint();

private:

	int m_Number;
	Player* m_Player;
	Shader* m_TextShader;
	Shader* m_DefaultShader;
	Shader* m_TileShader;
	std::vector<Tile> m_LevelGeometry;
	std::vector<AABB> m_StaticGeometry;
	std::vector<Door> m_Doors;
	std::vector<Enemy> m_Enemies;
	std::vector<Item> m_Items;
	std::vector<Pickup> m_Pickups;
	std::vector<HiddenDoor> m_HiddenDoors;
	std::vector<Elevator> m_Elevators;
	glm::vec3 m_SpawnPoint;
	glm::vec3 m_Endpoint;
	glm::ivec2 m_LevelDimensions;
	int FlatIndex(int x, int y);
	bool ClosestCollision(Ray& ray, Actor* actor);
	bool CompareLengths(glm::vec3 const& length_one, glm::vec3 const& length_two);
};