#pragma once

#include "CoreEngine.h"
#include "Game.h"
#include "Window.h"
#include "TimeManager.h"
#include "Input.h"

#define FRAME_CAP 5000; 

int main()
{
	CoreEngine engine;
	engine.Run();

	return 0;
}

CoreEngine::CoreEngine()
{
	m_Window.Create(800, 600);
	m_ResourceManager.Create();

	m_Game = new Game();
	m_IsActive = false;
}

void CoreEngine::Run()
{
	m_IsActive = true;

	int frames = 0;

	double last_time = TimeManager::GetTime();
	double unprocessed_time = 0;
	double frame_counter = 0;

	double frame_time = 1.0 / FRAME_CAP;
	
	while (m_IsActive)
	{
		Render();
		//bool render = false;

		//double start_time = TimeManager::GetTime();
		//double passed_time = start_time - last_time;
		//last_time = start_time;

		//unprocessed_time += passed_time;
		//frame_counter += passed_time;

		//if (frame_counter >= 1.0)
		//{
		//	frames = 0;
		//	frame_counter = 0;
		//}

		//while (unprocessed_time > frame_time)
		//{
		//	render = true;

		//	TimeManager::SetDelta(frame_time);

		//	Input::Update();

		//	m_Game->Input();
		//	m_Game->Update();

		//	Render();

		//	unprocessed_time -= frame_time;
		//}

		//if (render)	
		//{
		//	//Render();
		//	frames++;
		//}
		//else 
		//{
		//	// SLEEP FOR ONE MILLI
		//}
	}

	Destroy();
}

void CoreEngine::Render()
{
	Window::Get()->Clear();
	m_Game->Render();
	Window::Get()->SwapAndPoll();
}

void CoreEngine::Destroy()
{
	Window::Get()->Destroy();
}