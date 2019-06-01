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
	void ResetGame();
	bool GetActive();

private:

	bool m_IsActive = false;
	Level* m_Level;
	Player* m_Player_;
	Audio* m_Audio;
};