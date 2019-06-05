#pragma once

#include "ResourceManager.h"
#include "WindowManager.h"
#include "AudioManager.h"
#include "GameManager.h"

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

	WindowManager m_WindowManager;
	ResourceManager m_ResourceManager;
	AudioManager m_AudioManager;
	GameManager m_GameManager;
};