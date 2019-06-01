#pragma once

class Game;

class CoreEngine
{
public:

	CoreEngine();
	void Start();
	void Stop();
	void Run();
	void Render();
	void Destroy();

private:

	bool m_IsActive = false;
	Game* m_Game;
};