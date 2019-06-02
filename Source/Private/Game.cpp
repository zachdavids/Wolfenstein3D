#include "Game.h"
#include "Level.h"
#include "Player.h"
#include "AudioManager.h"
#include "WindowManager.h"

#include <GLFW/glfw3.h>

Game::Game()
{
	m_Player_ = new Player(glm::vec3(1.5f, 0.4375f, 1.5f), 0, 0);
	m_Level = new Level("Level1.xml", m_Player_);

	m_IsActive = true;
}

//TODO FIX
void Game::ResetGame()
{
	delete m_Player_;
	delete m_Level;

	m_Player_ = new Player(glm::vec3(1.5f, 0.4375f, 1.5f), 0, 0);
	m_Level = new Level("Level1.xml", m_Player_);
}

void Game::Input()
{
	m_Level->Input();

	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_ESCAPE))
	{
		m_IsActive = false;
		exit(0);
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_R))
	{
		ResetGame();
	}
}

void Game::Update()
{
	m_Level->Update();
}

void Game::Render()
{
	m_Level->Render();
}

bool Game::GetActive()
{
	return m_IsActive;
}