#ifndef COREENGINE_H	
#define COREENGINE_H

#include "Window.h"
#include "TimeManager.h"
#include "Game.h"
#include "Input.h"
#include "RenderUtility.h"
#include <iostream>

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
	bool is_running_;
	Game* game_;
};

#endif