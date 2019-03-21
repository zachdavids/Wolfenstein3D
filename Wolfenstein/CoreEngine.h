#pragma once

#include "Window.h"
#include "Time.h"
#include "Game.h"
#include "Input.h"
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