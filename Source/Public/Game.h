#ifndef GAME_H
#define GAME_H

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

#endif