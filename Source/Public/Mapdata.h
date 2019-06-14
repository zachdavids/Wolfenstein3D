#pragma once

#include "Door.h"
#include "Enemy.h"
#include "Medkit.h"
#include "Wall.h"

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
	std::vector<Medkit> items;
	std::vector<AABB> collision;
};