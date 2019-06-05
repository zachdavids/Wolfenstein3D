#pragma once

class Level;
class Player;

class GameManager
{
public:

	GameManager() = default;
	void Create();
	void Input();
	void Update();
	void Render();
	void ResetGame();
	bool GetActive();
	Player* GetPlayer();
	static GameManager* Get() { return m_Instance; }

private:

	static GameManager* m_Instance;
	bool m_bIsActive = false;
	Level* m_Level;
	Player* m_Player;
};