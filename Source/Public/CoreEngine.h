#pragma once

#include "Window.h"
#include "ResourceManager.h"

class Game;

class CoreEngine
{
public:

	CoreEngine();
	void Run();
	void Render();
	void Destroy();

private:

	bool m_IsActive = false;
	Window m_Window;
	ResourceManager m_ResourceManager;
	Game* m_Game;
};