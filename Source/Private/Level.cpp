#include "Level.h"

#include "Player.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "XMLParser.h"

#include <GLM/glm.hpp>
#include <GLFW/glfw3.h>
#include <GLM/gtc/constants.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>

const float FLOOR_LENGTH = 1.0f;
const float FLOOR_WIDTH = 1.0f;
const float CEILING_HEIGHT = 1.0f;

const float DOOR_LENGTH = 0.125f;
const float DOOR_WIDTH = 1.0f;
const float DOOR_HEIGHT = 1.0f;

const int PLAYER_DAMAGE = 34;

const int NUM_TEXTURES_X = 6;
const int NUM_TEXTURES_Y = 19;

static glm::vec2 dimensions_;

static std::vector<Node> nodes_;

static std::vector<glm::vec3> collision_start;
static std::vector<glm::vec3> collision_end;

static int nearest_enemy_num;
static std::vector<Door> doors_temp_;
static std::vector<Enemy> enemies_temp_; 

Level::Level(std::string filename)
{
	nearest_enemy_num = -1;

	m_Player = GameManager::Get()->GetPlayer();
	m_DefaultShader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_TextShader = ResourceManager::Get()->GetResource<Shader>("TextShader");

	GenerateLevel(filename);

	AudioManager::Get()->PlayMusic();
}

void Level::Input()
{
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_E)) {
		OpenDoors(m_Player->m_Transform.GetPosition(), true);
	}

	m_Player->Input();

	for (unsigned int i = 0; i < enemies_.size(); i++) {
		OpenDoors(enemies_[i].GetTranslation(), false);
	}
}

void Level::Update()
{
	for (unsigned int i = 0; i < doors_.size(); i++) {
		doors_[i].Update();
	}

	m_Player->Update();

	for (unsigned int i = 0; i < enemies_.size(); i++) {
		enemies_[i].Update();
	}

	for (unsigned int i = 0; i < medkits_.size(); i++) {
		medkits_[i].Update();
	}

	if (nearest_enemy_num != -1) {
		enemies_[nearest_enemy_num].Damage(PLAYER_DAMAGE);
		nearest_enemy_num = -1;
	}

	RemoveMedkit();
}

void Level::Render()
{
	//TODO Move Rendering to a Rendering Engine
	//Seperate objects by shader to reduce binds and group by mesh
	//to reduce vao bind calls.

	m_DefaultShader->Bind();
	m_DefaultShader->SetMat4("projection", m_Player->GetCamera()->GetProjectionMatrix());
	m_DefaultShader->SetMat4("view", m_Player->GetCamera()->GetViewMatrix());

	m_TextShader->Bind();
	m_TextShader->SetVec3("color", glm::vec3(0.5, 0.8f, 0.2f));
	m_TextShader->SetMat4("projection", glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));

	for (Wall wall : m_LevelGeometry)
	{
		wall.Render();
	}

	for (unsigned int i = 0; i < doors_.size(); i++) {
		doors_[i].Render();
	}

	for (unsigned int i = 0; i < enemies_.size(); i++) {
		enemies_[i].Render();
	}

	for (unsigned int i = 0; i < medkits_.size(); i++) {
		medkits_[i].Render();
	}

	m_Player->Render();
}

void Level::OpenDoors(glm::vec3 position, bool exit)
{
	for (unsigned int i = 0; i < doors_.size(); i++) {
		if (glm::length(doors_[i].GetPosition() - position) < 1.0f) {
			doors_[i].Open();
		}
	}
	if (exit) {
		for (unsigned int i = 0; i < endpoints_.size(); i++) {
			if (glm::length(endpoints_[i] - position) < 1.0f) {
				//audio_->PlayLevelEnd();
				//Game::LoadNextLevel();
			}
		}
	}
}

void Level::GenerateLevel(std::string const& file_name)
{
	/**/
	XMLParser parser(file_name);
	if (!parser.TryParse())
	{
		std::cout << "Error parsing level file\n";
		return;
	}

	nodes_ = parser.GetNodes();
	dimensions_ = parser.GetDimensions();

	for (int i = 0; i < dimensions_.x; i++) 
	{
		for (int j = 0; j < dimensions_.y; j++) 
		{
			if (nodes_[i * dimensions_.x + j].m_Node.test(Node::NodeType::Location)) 
			{
				//Floor
				m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 0, j), glm::vec3(0.0f), Wall::Type::kFloor));

				//Ceiling
				m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j), glm::vec3(0.0f), Wall::Type::kCeiling));

				//Wall
				if (!nodes_[i * dimensions_.x + (j - 1)].m_Node.test(Node::NodeType::Location)) 
				{
					m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f), Wall::Type::kWall));
					collision_start.push_back(glm::vec3(i * FLOOR_WIDTH, 0, j * FLOOR_WIDTH));
					collision_end.push_back(glm::vec3((i + 1) * FLOOR_WIDTH, 0, j * FLOOR_WIDTH));
				}

				if (!nodes_[i * dimensions_.x + (j + 1)].m_Node.test(Node::NodeType::Location)) 
				{
					m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j + 1), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f), Wall::Type::kWall));
					collision_start.push_back(glm::vec3(i * FLOOR_WIDTH, 0, (j + 1) * FLOOR_WIDTH));
					collision_end.push_back(glm::vec3((i + 1) * FLOOR_WIDTH, 0, (j + 1) * FLOOR_WIDTH));
				}

				if (!nodes_[(i - 1) * dimensions_.x + j].m_Node.test(Node::NodeType::Location)) 
				{
					m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j), glm::vec3(glm::radians(90.0f), 0.0f, glm::radians(90.0f)), Wall::Type::kWall));
					collision_start.push_back(glm::vec3(i * FLOOR_WIDTH, 0, j * FLOOR_WIDTH));
					collision_end.push_back(glm::vec3(i * FLOOR_WIDTH, 0, (j + 1) * FLOOR_WIDTH));
				}

				if (!nodes_[(i + 1) * dimensions_.x + j].m_Node.test(Node::NodeType::Location)) 
				{
					m_LevelGeometry.emplace_back(Wall(glm::vec3(i + 1, 1, j), glm::vec3(glm::radians(90.0f), 0.0f, glm::radians(90.0f)), Wall::Type::kWall));
					collision_start.push_back(glm::vec3((i + 1) * FLOOR_WIDTH, 0, j * FLOOR_WIDTH));
					collision_end.push_back(glm::vec3((i + 1) * FLOOR_WIDTH, 0, (j + 1) * FLOOR_WIDTH));
				}
			}
			// Door Generation
			if (nodes_[i * dimensions_.x + j].m_Node.test(Node::NodeType::Door)) 
			{
				bool x_orientation = ((!nodes_[i * dimensions_.x + (j - 1)].m_Node.test(Node::NodeType::Location)) && 
					(!nodes_[i * dimensions_.x + (j - 1)].m_Node.test(Node::NodeType::Location)));
				if (x_orientation)
				{
					doors_.push_back(Door(glm::vec3(i, 0, j), true));
				}
				else
				{
					doors_.push_back(Door(glm::vec3(i, 0, j), false));
				}
				doors_temp_ = doors_;
			}
			//Enemy
			if (nodes_[i * dimensions_.x + j].m_Node.test(Node::NodeType::Enemy)) 
			{
				enemies_.push_back(Enemy(glm::vec3(i, 0, j)));
			}
			//Medkit
			if (nodes_[i * dimensions_.x + j].m_Node.test(Node::NodeType::Medkit)) 
			{
				medkits_.push_back(Medkit(glm::vec3(i, 0, j)));
			}
			//Endpoint
			if (nodes_[i * dimensions_.x + j].m_Node.test(Node::NodeType::Endpoint)) 
			{
				endpoints_.push_back(glm::vec3(i, 0, j));
			}
		}
	}
	enemies_temp_ = enemies_;
}

glm::vec3 Level::CheckCollision(glm::vec3 old_position, glm::vec3 new_position, float width, float length)
{
	glm::vec3 collision_vector = glm::vec3(1, 0, 1);
	glm::vec3 movement_vector = new_position - old_position;

	if (movement_vector.length() > 0) {
		// Wall Collision
		glm::vec3 node_size(1, 0, 1);
		glm::vec3 object_size(width, 0, length);

		glm::vec3 old_position_2(old_position.x + 1, 0, old_position.z);
		glm::vec3 new_position_2(new_position.x + 1, 0, new_position.z);

		for (unsigned int i = 0; i < dimensions_.x; i++) {
			for (unsigned int j = 0; j < dimensions_.y; j++) {
				if (!nodes_[(i - 1) * dimensions_.x + j].m_Node.test(Node::NodeType::Location)) {
					collision_vector *= RectangularCollision(old_position_2, new_position_2, object_size, node_size * glm::vec3(i, 0, j), node_size);
				}
			}
		}

		// Door Collision
		old_position_2.x = old_position.x;
		new_position_2.x = new_position.x;

		for (unsigned int i = 0; i < doors_temp_.size(); i++) {
			node_size = doors_temp_[i].GetDimensions();
			collision_vector *= RectangularCollision(old_position_2, new_position_2, object_size, doors_temp_[i].GetPosition(), node_size);
		}
	}

	return collision_vector;
}

glm::vec3 Level::RectangularCollision(glm::vec3 old_position, glm::vec3 new_position, glm::vec3 size_1, glm::vec3 position_2, glm::vec3 size_2)
{
	glm::vec3 result(0.0f);

	if ((new_position.x + size_1.x < position_2.x) || (new_position.x - size_1.x > position_2.x + size_2.x * size_2.x) ||
		(old_position.z + size_1.z < position_2.z) || (old_position.z - size_1.z > position_2.z + size_2.z * size_2.z)) {
		result.x = 1;
	}

	if ((old_position.x + size_1.x < position_2.x) || (old_position.x - size_1.x > position_2.x + size_2.x * size_2.x) ||
		(new_position.z + size_1.z < position_2.z) || (new_position.z - size_1.z > position_2.z + size_2.z * size_2.z)) {
		result.z = 1;
	}

	return result;
}

glm::vec3 Level::CheckIntersection(glm::vec3 line_start, glm::vec3 line_end, bool attack)
{
	glm::vec3 nearest_intersection(NULL);

	for (unsigned int i = 0; i < collision_start.size(); i++) {
		glm::vec3 collision_vector = LineIntersection(line_start, line_end, collision_start[i], collision_end[i]);

		if (collision_vector != glm::vec3(NULL) && nearest_intersection == glm::vec3(NULL) ||
			glm::length(nearest_intersection - line_start) > glm::length(collision_vector - line_start)) {
			nearest_intersection = NearestIntersection(nearest_intersection, collision_vector, line_start);
		}
	}

	for (unsigned int i = 0; i < doors_temp_.size(); i++) {
		glm::vec3 collision_vector = LineIntersectionRectangle(line_start, line_end, doors_temp_[i].GetPosition(), doors_temp_[i].GetDimensions().x, doors_temp_[i].GetDimensions().y);

		if (collision_vector != glm::vec3(NULL) && nearest_intersection == glm::vec3(NULL) ||
			glm::length(nearest_intersection - line_start) > glm::length(collision_vector - line_start)) {
			nearest_intersection = NearestIntersection(nearest_intersection, collision_vector, line_start);
		}
	}

	if (attack) {
		glm::vec3 nearest_enemy_intersection(NULL);
		glm::vec3 collision_vector(NULL);

		for (unsigned int i = 0; i < enemies_temp_.size(); i++) {
			glm::vec3 collision_vector = LineIntersectionRectangle(line_start, line_end, enemies_temp_[i].GetTranslation(), enemies_temp_[i].GetSize().x, enemies_temp_[i].GetSize().y);

			glm::vec3 last_enemy_intersection = nearest_enemy_intersection;
			nearest_enemy_intersection = NearestIntersection(nearest_intersection, collision_vector, line_start);

			if (nearest_enemy_intersection == collision_vector) {
				nearest_enemy_num = i;
			}
			else {
			}
		}
	}

	return nearest_intersection;
}

glm::vec3 Level::LineIntersection(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 line_start2, glm::vec3 line_end2)
{
	glm::vec3 line_1 = line_end - line_start;
	glm::vec3 line_2 = line_end2 - line_start2;

	float cross = (line_1.x * line_2.z) - (line_1.z * line_2.x);

	if (cross == 0) {
		return glm::vec3(NULL);
	}

	glm::vec3 distance_between = line_start2 - line_start;

	float a = ((distance_between.x * line_2.z) - (distance_between.z * line_2.x)) / cross;
	float b = ((distance_between.x * line_1.z) - (distance_between.z * line_1.x)) / cross;

	if ((a > 0.0f && a < 1.0f) && (b > 0.0f && b < 1.0f)) {
		return line_start + (line_1 * a);
	}

	return glm::vec3(NULL);
}

glm::vec3 Level::LineIntersectionRectangle(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 position, float width, float length)
{
	glm::vec3 result = glm::vec3(NULL);

	glm::vec3 collision_vector = LineIntersection(line_start, line_end, position, glm::vec3(position.x + width, 0, position.z));
	result = NearestIntersection(result, collision_vector, line_start);

	collision_vector = LineIntersection(line_start, line_end, position, glm::vec3(position.x, 0, position.z + length));
	result = NearestIntersection(result, collision_vector, line_start);

	collision_vector = LineIntersection(line_start, line_end, glm::vec3(position.x, 0, position.z + length), glm::vec3(position.x + width, 0, position.z + length));
	result = NearestIntersection(result, collision_vector, line_start);

	collision_vector = LineIntersection(line_start, line_end, glm::vec3(position.x + width, 0, position.z), glm::vec3(position.x + width, 0, position.z + length));
	result = NearestIntersection(result, collision_vector, line_start);

	return result;
}

glm::vec3 Level::NearestIntersection(glm::vec3 line_1, glm::vec3 line_2, glm::vec3 nearest)
{
	if (line_2 != glm::vec3(NULL) && line_1 == glm::vec3(NULL) ||
		glm::length(line_1 - nearest) > glm::length(line_2 - nearest)) {
		return line_2;
	}
	else {
	}
	return line_1;
}

void Level::RemoveMedkit()
{
	for (unsigned int i = 0; i < medkits_.size(); i++) {
		if (medkits_[i].GetEaten()) {
			medkits_.erase(medkits_.begin() + i);
		}
	}
}
