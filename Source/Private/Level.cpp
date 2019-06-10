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
#include "AABB.h"
#include "Ray.h"
#include "Collision.h"

#include <GLM/glm.hpp>
#include <GLFW/glfw3.h>
#include <GLM/gtc/constants.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <iostream>
#include <algorithm>

const int PLAYER_DAMAGE = 34;

Level::Level(std::string const& filename)
{
	m_Player = GameManager::Get()->GetPlayer();
	m_DefaultShader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_TextShader = ResourceManager::Get()->GetResource<Shader>("TextShader");

	GenerateLevel(filename);

	AudioManager::Get()->PlayMusic();
}

void Level::Input()
{
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_E)) 
	{
		OpenDoors(m_Player->m_Transform.GetPosition(), true);
	}

	m_Player->Input();

	for (unsigned int i = 0; i < enemies_.size(); i++) 
	{
		OpenDoors(enemies_[i].GetTranslation(), false);
	}
}

void Level::Update()
{
	for (unsigned int i = 0; i < doors_.size(); i++) 
	{
		doors_[i].Update();
	}

	m_Player->Update();

	for (unsigned int i = 0; i < enemies_.size(); i++) 
	{
		enemies_[i].Update();
	}

	for (unsigned int i = 0; i < medkits_.size(); i++) 
	{
		medkits_[i].Update();
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

	for (unsigned int i = 0; i < doors_.size(); i++) 
	{
		doors_[i].Render();
	}

	for (unsigned int i = 0; i < enemies_.size(); i++) 
	{
		enemies_[i].Render();
	}

	for (unsigned int i = 0; i < medkits_.size(); i++) 
	{
		medkits_[i].Render();
	}

	m_Player->Render();
}

void Level::OpenDoors(glm::vec3& position, bool exit)
{
	for (unsigned int i = 0; i < doors_.size(); i++) 
	{
		if (glm::length(doors_[i].GetPosition() - position) < 1.0f) 
		{
			doors_[i].Open();
		}
	}
	if (exit) 
	{
		for (unsigned int i = 0; i < endpoints_.size(); i++) 
		{
			if (glm::length(endpoints_[i] - position) < 1.0f) 
			{
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

	std::vector<Node> nodes = parser.GetNodes();
	glm::vec2 dimensions = parser.GetDimensions();

	for (int i = 0; i < dimensions.x; i++)
	{
		for (int j = 0; j < dimensions.y; j++)
		{
			if (nodes[i * dimensions.x + j].m_Node.test(Node::NodeType::Location))
			{
				//Floor
				m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 0, j), glm::vec3(0.0f), Wall::Type::kFloor));

				//Ceiling
				m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j), glm::vec3(0.0f), Wall::Type::kCeiling));

				//Wall
				if (!nodes[i * dimensions.x + (j - 1)].m_Node.test(Node::NodeType::Location))
				{
					m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f), Wall::Type::kWall));
				}

				if (!nodes[i * dimensions.x + (j + 1)].m_Node.test(Node::NodeType::Location))
				{
					m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j + 1), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f), Wall::Type::kWall));
				}

				if (!nodes[(i - 1) * dimensions.x + j].m_Node.test(Node::NodeType::Location))
				{
					m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j), glm::vec3(glm::radians(90.0f), 0.0f, glm::radians(90.0f)), Wall::Type::kWall));
				}

				if (!nodes[(i + 1) * dimensions.x + j].m_Node.test(Node::NodeType::Location))
				{
					m_LevelGeometry.emplace_back(Wall(glm::vec3(i + 1, 1, j), glm::vec3(glm::radians(90.0f), 0.0f, glm::radians(90.0f)), Wall::Type::kWall));
				}

				// Door Generation
				if (nodes[i * dimensions.x + j].m_Node.test(Node::NodeType::Door))
				{
					bool x_orientation = ((!nodes[i * dimensions.x + (j - 1)].m_Node.test(Node::NodeType::Location)) &&
						(!nodes[i * dimensions.x + (j - 1)].m_Node.test(Node::NodeType::Location)));
					if (x_orientation)
					{
						doors_.push_back(Door(glm::vec3(i, 0, j), true));
					}
					else
					{
						doors_.push_back(Door(glm::vec3(i, 0, j), false));
					}
				}
				//Enemy
				if (nodes[i * dimensions.x + j].m_Node.test(Node::NodeType::Enemy))
				{
					enemies_.push_back(Enemy(glm::vec3(i, 0, j)));
				}
				//Medkit
				if (nodes[i * dimensions.x + j].m_Node.test(Node::NodeType::Medkit))
				{
					medkits_.push_back(Medkit(glm::vec3(i, 0, j)));
				}
				//Endpoint
				if (nodes[i * dimensions.x + j].m_Node.test(Node::NodeType::Endpoint))
				{
					endpoints_.push_back(glm::vec3(i, 0, j));
				}
			}
			else
			{
				AABB box;
				box.m_Min = glm::vec3(i, 0, j);
				box.m_Max = glm::vec3(i + 1, 0, j + 1);
				box.m_Position.x = (box.m_Max.x + box.m_Min.x) / 2;
				box.m_Position.z = (box.m_Max.z + box.m_Min.z) / 2;
				m_CollisionGeometry.emplace_back(box);
			}
		}
	}
}

bool Level::CheckRayCollision(Ray& ray)
{
	std::vector<Enemy*> EnemyCollisions;
	for (Enemy& enemy : enemies_)
	{
		if (Collision::RayAABBIntersection(ray, enemy.GetAABB()))
		{
			EnemyCollisions.emplace_back(&enemy);
		}
	}

	if (EnemyCollisions.size() > 0)
	{
		std::sort(EnemyCollisions.begin(), EnemyCollisions.end(),
			[&ray](Enemy* enemy_one, Enemy* enemy_two) -> bool
			{
				float distance_one = glm::length(enemy_one->m_Transform.GetPosition() - ray.m_Origin);
				float distance_two = glm::length(enemy_two->m_Transform.GetPosition() - ray.m_Origin);
				return distance_one < distance_two;
			}
		);

		for (AABB& box : m_CollisionGeometry)
		{
			if (Collision::RayAABBIntersection(ray, box))
			{
				float enemy_distance = glm::length(EnemyCollisions[0]->m_Transform.GetPosition() - ray.m_Origin);
				float wall_distance = glm::length(box.m_Position - ray.m_Origin);
				if (wall_distance < enemy_distance)
				{
					return false;
				}
			}
		}
		EnemyCollisions[0]->Damage(PLAYER_DAMAGE);
		return true;
	}
	return false;
}

bool Level::CheckAABBCollision(AABB& one)
{
	for (AABB& box: m_CollisionGeometry)
	{
		if (Collision::AABBIntersection(one, box))
		{
			return true;
		}
	}
	return false;
}

void Level::RemoveMedkit()
{
	for (unsigned int i = 0; i < medkits_.size(); i++) 
	{
		if (medkits_[i].GetEaten()) 
		{
			medkits_.erase(medkits_.begin() + i);
		}
	}
}
