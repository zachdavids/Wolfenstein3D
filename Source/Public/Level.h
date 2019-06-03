#pragma once

#include "Player.h"
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
#include "XMLParser.h"
#include "Node.h"
#include "Door.h"
#include "Enemy.h"
#include "Medkit.h"
#include "AudioManager.h"
#include "Wall.h"

#include <GLM/gtx\rotate_vector.hpp>
#include <string>

class Door;
class Enemy;
class Player;
class Medkit;

class Level
{
public:

	Level(std::string filename, Player* player);

	void Input();
	void Update();
	void Render();

	void OpenDoors(glm::vec3 position, bool exit);

	static glm::vec3 CheckCollision(glm::vec3 old_position, glm::vec3 new_position, float width, float length);
	static glm::vec3 RectangularCollision(glm::vec3 old_position, glm::vec3 new_position, glm::vec3 size_1, glm::vec3 position_2, glm::vec3 size_2);
	static glm::vec3 CheckIntersection(glm::vec3 line_start, glm::vec3 line_end, bool attack);
	static glm::vec3 LineIntersection(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 line_start2, glm::vec3 line_end2);
	static glm::vec3 LineIntersectionRectangle(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 position, float width, float length);
	static glm::vec3 NearestIntersection(glm::vec3 line_1, glm::vec3 line_2, glm::vec3 nearest);

private:

	Player* player_;
	Camera* camera_;
	Transform* transform_;
	Mesh* mesh_;
	Enemy* enemy_;

	std::vector<Wall> m_LevelGeometry;
	std::vector<Door> doors_;
	std::vector<Enemy> enemies_;
	std::vector<Medkit> medkits_;
	std::vector<glm::vec3> endpoints_;

	void AddDoor(glm::vec3 position, bool x_orientation, bool y_orientation);

	void GenerateLevel(std::string const& file_name);
	void RemoveMedkit();
};