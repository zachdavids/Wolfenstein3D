#include "GameManager.h"
#include "Level.h"
#include "Player.h"
#include "AudioManager.h"
#include "WindowManager.h"

#include <GLFW/glfw3.h>

GameManager* GameManager::m_Instance;

void GameManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	m_Player = new Player(glm::vec3(1.5f, 0.4375f, 1.5f), glm::vec3(0.0f));
	m_Level = new Level("Level1.xml");
}

//TODO FIX
void GameManager::ResetGame()
{
	delete m_Player;
	delete m_Level;

	m_Player = new Player(glm::vec3(1.5f, 0.4375f, 1.5f), glm::vec3(0.0f));
	m_Level = new Level("Level1.xml");
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

bool GameManager::GetActive()
{
	return m_bIsActive;
}

Player* GameManager::GetPlayer()
{
	return m_Player;
}

Level* GameManager::GetLevel()
{
	return m_Level;
}
