#include "GameManager.h"
#include "AudioManager.h"
#include "WindowManager.h"

#include <GLFW/glfw3.h>

GameManager* GameManager::m_Instance;

void GameManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	m_Player = std::make_unique<Player>(glm::vec3(1.5f, 0.4375f, 1.5f), glm::vec3(0.0f));
	m_Level = std::make_unique<Level>("Level1.json");
}

//TODO FIX
void GameManager::ResetGame()
{
	m_Level->GenerateLevel("Level1.json");
}

void GameManager::Input()
{
	m_Level->Input();

	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_ESCAPE))
	{
		m_bIsActive = false;
		exit(0);
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_R))
	{
		ResetGame();
	}
}

void GameManager::Update()
{
	m_Level->Update();
}

void GameManager::Render()
{
	m_Level->Render();
}

void GameManager::StartGame()
{
	m_bIsActive = true;
}

bool GameManager::GetActive()
{
	return m_bIsActive;
}

void GameManager::EndGame()
{
	m_bIsActive = false;
}

Player* GameManager::GetPlayer()
{
	return m_Player.get();
}

Level* GameManager::GetLevel()
{
	return m_Level.get();
}
