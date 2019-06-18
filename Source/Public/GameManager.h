#pragma once

#include "Level.h"
#include "Player.h"

#include <memory>

class GameManager
{
public:

	GameManager() = default;
	void Create();
	void Input();
	void Update();
	void Render();
	void StartGame();
	void ResetGame();
	bool GetActive();
	void EndGame();
	Player* GetPlayer();
	Level* GetLevel();
	static GameManager* Get() { return m_Instance; }

private:

	static GameManager* m_Instance;
	bool m_bIsActive = false;
	std::unique_ptr<Level> m_Level;
	std::unique_ptr<Player> m_Player;
};