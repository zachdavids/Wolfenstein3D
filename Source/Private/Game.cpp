#include "Game.h"
#include "Level.h"
#include "Player.h"
#include "Audio.h"

Game::Game()
{
	player_ = new Player(glm::vec3(1.5f, 0.4375f, 1.5f), 0, 0);
	level_ = new Level("Level1.xml", "Tiles/TileTextures.png", player_);
	m_IsActive = true;
	audio_ = new Audio();
}

//void Game::GameOver()
//{
//	audio_->PlayPlayerDeath();
//	m_IsActive = false;
//}

void Game::Input()
{
	level_->Input();

	if (Input::GetKeyPressed(Input::KEY_ESCAPE))
	{
		exit(0);
	}
	if (Input::GetKeyPressed(Input::KEY_R))
	{
		delete player_;
		player_ = new Player(glm::vec3(1.5f, 0.4375f, 1.5f), 0, 0);
		delete level_;
		level_ = new Level("Level1.xml", "TileTextures.png", player_);
		m_IsActive = true;
	}
}

void Game::Update()
{
	level_->Update();
}

void Game::Render()
{
	level_->Render();
}