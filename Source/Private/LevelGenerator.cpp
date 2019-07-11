#include "LevelGenerator.h"
#include "ResourceManager.h"
#include "Tile.h"
#include "Pickup.h"
#include "Enemy.h"

#include <GLM/trigonometric.hpp>
#include <GLM/common.hpp>

#include <vector>
#include <fstream>

using json = nlohmann::json;

Mapdata LevelGenerator::Generate(std::string const& filename)
{
	std::ifstream file(s_Directory + filename);
	json data;
	file >> data;
	file.close();

	ResourceManager::Get()->LoadLevelResources(data["resources"]);

	Mapdata map;
	map.number = data["number"];

	GenerateGeometry(data["layers"][0], map);
	GenerateObjects(data["layers"][1], map);

	return map;
}

void LevelGenerator::GenerateGeometry(json& layer, Mapdata& map)
{
	Mesh* wall_tile = ResourceManager::Get()->GetResource<Mesh>("WallTile");
	Mesh* door_tile = ResourceManager::Get()->GetResource<Mesh>("DoorTile");

	int index = 0;
	for (auto& t_id : layer["data"])
	{
		glm::vec3 position = glm::vec3(-index % s_MapSize, 0, s_MapSize - glm::floor(index / s_MapSize));
		glm::vec3 rotation = (t_id % 2 == 0) ? glm::vec3(0, 0, 0) : glm::vec3(0, glm::radians(90.0f), 0);
		if (t_id > 0 && t_id <= 98 || t_id == 107)
		{
			map.geometry.emplace_back(Tile(position, rotation, 198 - t_id, wall_tile));
			map.collision.emplace_back(BoundingBox{ position, glm::vec3(0.5f, 0, 0.5f) });
		}
		else if (t_id == 99 || t_id == 100 || t_id == 106)
		{
			map.geometry.emplace_back(Tile(position, rotation, 96, door_tile));
			map.doors.emplace_back(Door(position, rotation, 198 - t_id));
		}
		++index;
	}
}

void LevelGenerator::GenerateObjects(nlohmann::json& layer, Mapdata& map)
{
	int index = 0;
	for (auto& object : layer["objects"])
	{
		switch (object["id"].get<int>())
		{
		case 1:
			map.spawn.position = glm::vec3(-object["x"], object["y"], object["z"]);
			map.spawn.rotation = glm::vec3(0, glm::radians(object["rotation"].get<float>()), 0);
			break;
		case 2:
			map.items.emplace_back(Item(
				glm::vec3(-object["x"], object["y"], object["z"]),
				object["texture"]
			));
			if (object["collision"].get<int>() == 1)
			{
				map.collision.emplace_back(BoundingBox{
					glm::vec3(-object["x"], object["y"], object["z"]),
					glm::vec3(0.5f, 0, 0.5f)
					});
			}
			break;
		case 3:
			map.pickups.emplace_back(Pickup(
				glm::vec3(-object["x"], object["y"], object["z"]),
				object["type"], 
				object["texture"],
				object["amount"]
			));
			break;
		case 4:
			map.enemies.emplace_back(Enemy(
				glm::vec3(-object["x"], object["y"], object["z"])
			));
			break;
		case 5:
			map.hidden.emplace_back(HiddenDoor(
				glm::vec3(-object["x"], object["y"], object["z"]),
				glm::vec3(-object["cx"], object["cy"], object["cz"]),
				glm::vec3(0, 0, 0),
				198 - object["texture"]
			));
			break;
		case 6:
			map.elevators.emplace_back(Elevator(
				glm::vec3(-object["x"], object["y"], object["z"]),
				glm::vec3(0, 0, 0),
				90
			));
		}
	}
}

glm::vec3 LevelGenerator::CalcPos(int index)
{
	return glm::vec3(index % s_MapSize, 0, s_MapSize - glm::floor(index / s_MapSize));
}

