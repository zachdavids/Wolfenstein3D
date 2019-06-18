#include "Level.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Shader.h"
#include "Camera.h"
#include "Collision.h"

#include "LevelGenerator.h"

#include <iostream>
#include <algorithm>
#include <GLM/geometric.hpp>
#include <GLM/gtc/matrix_transform.hpp>

const int PLAYER_DAMAGE = 34;

Level::Level(std::string const& filename)
{
	m_Player = GameManager::Get()->GetPlayer();

	m_DefaultShader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_TileShader = ResourceManager::Get()->GetResource<Shader>("TileShader");
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

	for (Item& item : m_Items)
	{
		item.Update();
	}

	for (Pickup& pickup : m_Pickups)
	{
		pickup.Update();
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

	m_TileShader->Bind();
	m_TileShader->SetMat4("projection", m_Player->GetCamera()->GetProjectionMatrix());
	m_TileShader->SetMat4("view", m_Player->GetCamera()->GetViewMatrix());

	m_TextShader->Bind();
	m_TextShader->SetVec3("color", glm::vec3(0.5, 0.8f, 0.2f));
	m_TextShader->SetMat4("projection", glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));

	for (Wall& Wall : m_LevelGeometry)
	{
		Wall.Render();
	}

	for (Door& door : m_Doors) 
	{
		door.Render();
	}

	for (Enemy& enemy : m_Enemies) 
	{
		enemy.Render();
	}

	for (Item& item : m_Items) 
	{
		item.Render();
	}

	for (Pickup& pickup : m_Pickups)
	{
		pickup.Render();
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
	Mapdata map;
	LevelGenerator level_gen;
	map = level_gen.Generate("Level1.json");

	m_Number = map.number;
	m_SpawnPoint = map.spawn.position;
	m_LevelGeometry = map.geometry;
	m_StaticGeometry = map.collision;
	m_Doors = map.doors;
	m_Items = map.items;
	m_Pickups = map.pickups;
	m_Enemies = map.enemies;

	m_Player->GetCamera()->SetPosition(m_SpawnPoint);
	m_Player->GetCamera()->SetRotation(map.spawn.rotation);
}

bool Level::CheckPlayerRayCollision(Ray& ray, float range)
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
			if (glm::length(EnemyCollisions[0]->GetPosition() - ray.m_Origin) < range)
			{
				EnemyCollisions[0]->Damage(PLAYER_DAMAGE);
				return true;
			}
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
			if (CompareLengths(actor->GetPosition() - ray.m_Origin, box.position - ray.m_Origin))
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
			if (CompareLengths(actor->GetPosition() - ray.m_Origin, box.position - ray.m_Origin))
			{
				return false;
			}
		}
	}
	
	return true;
}

bool Level::CheckAABBCollision(AABB& actor, glm::vec3& normal, glm::vec3& position)
{
	AABB closest;
	for (AABB& box: m_StaticGeometry)
	{
		if (Collision::AABBIntersection(actor, box, normal, position))
		{
			if (CompareLengths(closest.position, box.position))
			{
				closest = box;
			}
		}
	}

	for (Door& door : m_Doors)
	{
		AABB box = door.GetAABB();
		if (Collision::AABBIntersection(actor, box, normal, position))
		{
			if (CompareLengths(closest.position, box.position))
			{
				closest = box;
			}
		}
	}
	return true;
}

int Level::GetLevelNumber()
{
	return m_Number;
}

glm::vec3 Level::GetSpawnPoint()
{
	return m_SpawnPoint;
}

//Returns true if first vector's length is over the second
bool Level::CompareLengths(glm::vec3 const& length_one, glm::vec3 const& length_two)
{
	float distance_one = glm::length(length_one);
	float distance_two = glm::length(length_two);

	return distance_one > distance_two;
}
