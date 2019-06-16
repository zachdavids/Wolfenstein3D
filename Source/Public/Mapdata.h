#pragma once

#include "Door.h"
#include "Enemy.h"
#include "Item.h"
#include "Wall.h"
#include "Pickup.h"

#include <vector>

struct SpawnPoint
{
	glm::vec3 position;
	glm::vec3 rotation;
};

struct Mapdata
{
	SpawnPoint spawn;
	glm::vec3 endpoint;
	std::vector<Wall> geometry;
	std::vector<Door> doors;
	std::vector<Enemy> enemies;
	std::vector<Item> items;
	std::vector<Pickup> pickups;
	std::vector<AABB> collision;
};