#include "Level.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Shader.h"
#include "Camera.h"
#include "LevelGenerator.h"
#include "Collision.h"

#include <iostream>
#include <algorithm>
#include <GLM/geometric.hpp>
#include <GLM/gtc/matrix_transform.hpp>

const int PLAYER_DAMAGE = 34;

Level::Level(std::string const& filename)
{
	m_Player = GameManager::Get()->GetPlayer();
	m_DefaultShader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_TextShader = ResourceManager::Get()->GetResource<Shader>("TextShader");

	AudioManager::Get()->PlayMusic();

	GenerateLevel(filename);
}

void Level::Input()
{
	m_Player->Input();

	for (Enemy& enemy : m_Enemies)
	{
		OpenDoors(enemy.GetPosition(), false);
	}
}

void Level::Update()
{
	m_Player->Update();

	for (Door& door : m_Doors)
	{
		door.Update();
	}

	for (Enemy& enemy : m_Enemies)
	{
		enemy.Update();
	}

	for (Medkit& medkit : m_Medkits)
	{
		medkit.Update();
	}
}

void Level::Render()
{
	//TODO Move Rendering to a Rendering Engine
	//Seperate objects by shader to reduce binds and group by mesh
	//to reduce vao bind calls.
	//Bind projection and view only if changed

	m_DefaultShader->Bind();
	m_DefaultShader->SetMat4("projection", m_Player->GetCamera()->GetProjectionMatrix());
	m_DefaultShader->SetMat4("view", m_Player->GetCamera()->GetViewMatrix());

	m_TextShader->Bind();
	m_TextShader->SetVec3("color", glm::vec3(0.5, 0.8f, 0.2f));
	m_TextShader->SetMat4("projection", glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));

	for (Wall& wall : m_LevelGeometry)
	{
		wall.Render();
	}

	for (Door& door : m_Doors) 
	{
		door.Render();
	}

	for (Enemy& enemy : m_Enemies) 
	{
		enemy.Render();
	}

	for (Medkit& medkit : m_Medkits) 
	{
		medkit.Render();
	}

	m_Player->Render();
}

void Level::OpenDoors(glm::vec3 const& position, bool exit)
{
	for (Door& door : m_Doors)
	{
		if (glm::length(door.GetPosition() - position) < 1.0f) 
		{
			door.Open();
		}
	}

	if (exit) 
	{
		if (glm::length(m_Endpoint - position) < 1.0f) 
		{
			//audio_->PlayLevelEnd();
			//Game::LoadNextLevel();
		}
	}
}

int Level::FlatIndex(int x, int y)
{
	return x * m_LevelDimensions.x + y;
}

void Level::GenerateLevel(std::string const& file_name)
{
	LevelGenerator parser(file_name);
	//if (!parser.TryParse())
	//{
	//	std::cout << "Error parsing level file\n";
	//	return;
	//}

	//std::vector<Node> nodes = parser.GetNodes();
	//m_LevelDimensions = parser.GetDimensions();

	//for (int i = 0; i < m_LevelDimensions.x; i++)
	//{
	//	for (int j = 0; j < m_LevelDimensions.y; j++)
	//	{
	//		if (nodes[FlatIndex(i, j)].m_Node.test(Node::NodeType::Location))
	//		{
	//			m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 0, j), glm::vec3(0.0f), Wall::Type::kFloor));
	//			m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j), glm::vec3(0.0f), Wall::Type::kCeiling));

	//			if (!nodes[FlatIndex(i, j - 1)].m_Node.test(Node::NodeType::Location))
	//			{
	//				m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f), Wall::Type::kWall));
	//			}

	//			if (!nodes[FlatIndex(i, j + 1)].m_Node.test(Node::NodeType::Location))
	//			{
	//				m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j + 1), glm::vec3(glm::radians(90.0f), 0.0f, 0.0f), Wall::Type::kWall));
	//			}

	//			if (!nodes[FlatIndex(i - 1, j)].m_Node.test(Node::NodeType::Location))
	//			{
	//				m_LevelGeometry.emplace_back(Wall(glm::vec3(i, 1, j), glm::vec3(glm::radians(90.0f), 0.0f, glm::radians(90.0f)), Wall::Type::kWall));
	//			}

	//			if (!nodes[FlatIndex(i + 1, j)].m_Node.test(Node::NodeType::Location))
	//			{
	//				m_LevelGeometry.emplace_back(Wall(glm::vec3(i + 1, 1, j), glm::vec3(glm::radians(90.0f), 0.0f, glm::radians(90.0f)), Wall::Type::kWall));
	//			}
	//			if (nodes[FlatIndex(i, j)].m_Node.test(Node::NodeType::Door))
	//			{
	//				bool positive_z = !nodes[FlatIndex(i, j - 1)].m_Node.test(Node::NodeType::Location);
	//				bool negative_z = !nodes[FlatIndex(i, j - 1)].m_Node.test(Node::NodeType::Location);
	//				if (positive_z && negative_z)
	//				{
	//					m_Doors.emplace_back(Door(glm::vec3(i, 0, j), true));
	//				}
	//				else
	//				{
	//					m_Doors.emplace_back(Door(glm::vec3(i, 0, j), false));
	//				}
	//			}
	//			if (nodes[FlatIndex(i, j)].m_Node.test(Node::NodeType::Enemy))
	//			{
	//				m_Enemies.emplace_back(Enemy(glm::vec3(i, 0, j)));
	//			}
	//			if (nodes[FlatIndex(i, j)].m_Node.test(Node::NodeType::Medkit))
	//			{
	//				m_Medkits.emplace_back(Medkit(glm::vec3(i, 0, j)));
	//			}
	//			if (nodes[FlatIndex(i, j)].m_Node.test(Node::NodeType::Endpoint))
	//			{
	//				m_Endpoint = glm::vec3(i, 0, j);
	//			}
	//		}
	//		else
	//		{
	//			AABB box;
	//			box.m_Min = glm::vec3(i, 0, j);
	//			box.m_Max = glm::vec3(i + 1, 0, j + 1);
	//			box.m_Position.x = (box.m_Max.x + box.m_Min.x) / 2;
	//			box.m_Position.z = (box.m_Max.z + box.m_Min.z) / 2;
	//			m_StaticGeometry.emplace_back(box);
	//		}
	//	}
	//}
}

bool Level::CheckPlayerRayCollision(Ray& ray)
{
	std::vector<Enemy*> EnemyCollisions;
	for (Enemy& enemy : m_Enemies)
	{
		if (Collision::RayAABBIntersection(ray, enemy.GetAABB()))
		{
			if (enemy.IsAlive())
			{
				EnemyCollisions.emplace_back(&enemy);
			}
		}
	}

	std::sort(EnemyCollisions.begin(), EnemyCollisions.end(),
		[&ray](Enemy* enemy_one, Enemy* enemy_two) -> bool
	{
		float distance_one = glm::length(enemy_one->GetPosition() - ray.m_Origin);
		float distance_two = glm::length(enemy_two->GetPosition() - ray.m_Origin);
		return distance_one < distance_two;
	});

	if (EnemyCollisions.size() > 0)
	{
		if (ClosestCollision(ray, EnemyCollisions[0]))
		{
			EnemyCollisions[0]->Damage(PLAYER_DAMAGE);
			return true;
		}
	}

	return false;
}

bool Level::CheckEnemyRayCollision(Ray& ray)
{
	if (Collision::RayAABBIntersection(ray, m_Player->GetAABB()) == false)
	{
		return false;
	}

	return ClosestCollision(ray, m_Player);
}

bool Level::ClosestCollision(Ray& ray, Actor* actor)
{
	for (AABB& box : m_StaticGeometry)
	{
		if (Collision::RayAABBIntersection(ray, box))
		{
			if (CompareLengths(actor->GetPosition() - ray.m_Origin, box.m_Position - ray.m_Origin))
			{
				return false;
			}
		}
	}

	for (Door& door : m_Doors)
	{
		AABB box = door.GetAABB();
		if (Collision::RayAABBIntersection(ray, box))
		{
			if (CompareLengths(actor->GetPosition() - ray.m_Origin, box.m_Position - ray.m_Origin))
			{
				return false;
			}
		}
	}
	
	return true;
}

bool Level::CompareLengths(glm::vec3 const& length_one, glm::vec3 const& length_two)
{
	float distance_one = glm::length(length_one);
	float distance_two = glm::length(length_two);

	return distance_one > distance_two;
}

bool Level::CheckAABBCollision(AABB& one)
{
	for (AABB& box: m_StaticGeometry)
	{
		if (Collision::AABBIntersection(one, box))
		{
			return true;
		}
	}

	for (Door& door : m_Doors)
	{
		AABB box = door.GetAABB();
		if (Collision::AABBIntersection(one, box))
		{
			return true;
		}
	}
	return false;
}
