#pragma once

#include "Time.h"
#include "Input.h"
#include "RenderUtility.h"

#include <iostream>

class Game;
class WindowManager;

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

	bool bIsRunning_;
	//todo convert to unique_ptrs
	Game* game_;
	WindowManager* windowManager_;
};