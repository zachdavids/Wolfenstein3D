#pragma once

#include "Level.h"
#include "Player.h"
#include "Audio.h"

class Level;
class Player;

class Game
{
public:

	Game();
	void Input();
	void Update();
	void Render();

	static void LoadNextLevel();
	static void GameOver();

private:

	int current_level_;
};