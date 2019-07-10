#pragma once

#include "Door.h"
#include "Enemy.h"
#include "Item.h"
#include "Tile.h"
#include "Pickup.h"
#include "HiddenDoor.h"
#include "Elevator.h"

#include <vector>

struct SpawnPoint
{
	glm::vec3 position;
	glm::vec3 rotation;
};

struct Mapdata
{
	int number;
	SpawnPoint spawn;
	glm::vec3 endpoint;
	std::vector<Tile> geometry;
	std::vector<Door> doors;
	std::vector<Enemy> enemies;
	std::vector<Item> items;
	std::vector<Pickup> pickups;
	std::vector<BoundingBox> collision;
	std::vector<HiddenDoor> hidden;
	std::vector<Elevator> elevators;
};