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

	glm::vec3 CheckCollision(glm::vec3 old_position, glm::vec3 new_position, float width, float length);
	glm::vec3 RectangularCollision(glm::vec3 old_position, glm::vec3 new_position, glm::vec3 size_1, glm::vec3 position_2, glm::vec3 size_2);
	glm::vec3 CheckIntersection(glm::vec3 line_start, glm::vec3 line_end, bool attack);
	bool LineIntersection(glm::vec3 l1_start, glm::vec3 l1_end, glm::vec3 l2_start, glm::vec3 l2_end, glm::vec3& result);
	glm::vec3 LineIntersectionRectangle(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 position, float width, float length);
	glm::vec3 NearestIntersection(glm::vec3 line_1, glm::vec3 line_2, glm::vec3 nearest);

	void TestProjectileCollision(Ray ray, Actor& hit);

private:

	Player* m_Player;
	Camera* camera_;
	Enemy* enemy_;

	Shader* m_TextShader; //temp
	Shader* m_DefaultShader; //temp

	std::vector<Wall> m_LevelGeometry;
	std::vector<Door> doors_;
	std::vector<Enemy> enemies_;
	std::vector<Medkit> medkits_;
	std::vector<glm::vec3> endpoints_;

	void GenerateLevel(std::string const& file_name);
	void RemoveMedkit();
};