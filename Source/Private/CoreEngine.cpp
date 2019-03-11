#include "CoreEngine.h"
#include "WindowManager.h"
#include "Game.h"

#define FRAME_CAP 5000; 

int main()
{
	return 0;
}

CoreEngine::CoreEngine()
{
	game_ = new Game();
	windowManager_ = new WindowManager();
	RenderUtility::GLInitialize();
	bIsRunning_ = false;
}

void CoreEngine::Start()
{
	if (bIsRunning_) { return; }

	Run();
}

void CoreEngine::Stop()
{
	if (!bIsRunning_) { return; }

	bIsRunning_ = false;
}

void CoreEngine::Run()
{
	bIsRunning_ = true;

	int frames = 0;

	double last_time = Time::GetTime();
	double unprocessed_time = 0;
	double frame_counter = 0;

	double frame_time = 1.0 / FRAME_CAP;
	
	while (bIsRunning_)
	{
		bool render = false;

		double start_time = Time::GetTime();
		double passed_time = start_time - last_time;
		last_time = start_time;

		unprocessed_time += passed_time;
		frame_counter += passed_time;

		if (frame_counter >= 1.0)
		{
			frames = 0;
			frame_counter = 0;
		}

		while (unprocessed_time > frame_time)
		{
			render = true;

			if (windowManager_->CloseRequested())
				Stop();

			Time::SetDelta(frame_time);

			Input::Update();

			game_->Input();
			game_->Update();

			Render();

			unprocessed_time -= frame_time;
		}

		if (render)	
		{
			//Render();
			frames++;
		}
		else 
		{
			// SLEEP FOR ONE MILLI
		}
	}

	Destroy();
}

void CoreEngine::Render()
{
	RenderUtility::ClearScreen();
	game_->Render();
	windowManager_->Render();
}

void CoreEngine::Destroy()
{
	windowManager_->Destroy();
}