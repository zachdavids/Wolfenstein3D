#include "Game.h"

static bool running_ = false;
static Level* level_;
static Player* player_;
static Audio* audio_;

Game::Game()
{
	player_ = new Player(glm::vec3(1.5f, 0.4375f, 1.5f), 0, 0);
	level_ = new Level("Level1.xml", "Tiles/TileTextures.png", player_);
	running_ = true;
	audio_ = new Audio();
}

void Game::GameOver()
{
	audio_->PlayPlayerDeath();
	running_ = false;
}

void Game::LoadNextLevel()
{
	delete player_;
	player_ = new Player(glm::vec3(1.5f, 0.4375f, 1.5f), 0, 0);
	delete level_;
	level_ = new Level("Level2.xml", "TileTextures.png", player_);
}

void Game::Input()
{
	if (running_) {
		level_->Input();
	}
	else {
		if (Input::GetKeyPressed(Input::KEY_ESCAPE)) {
			exit(0);
		}
		if (Input::GetKeyPressed(Input::KEY_R)) {
			delete player_;
			player_ = new Player(glm::vec3(1.5f, 0.4375f, 1.5f), 0, 0);
			delete level_;
			level_ = new Level("Level1.xml", "TileTextures.png", player_);
			running_ = true;
		}
	}
}

void Game::Update()
{
	if (running_) {
		level_->Update();
	}
}

void Game::Render()
{
	if (running_) {
		level_->Render();
	}
}