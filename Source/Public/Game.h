#pragma once

class Level;
class Player;
class Audio;

class Game
{
public:

	Game();

	void Input();
	void Update();
	void Render();

	//void GameOver();

private:

	bool m_IsActive = false;

	Level* level_;
	Player* player_;
	Audio* audio_;
};