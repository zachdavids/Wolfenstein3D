#include "CoreEngine.h"

#define FRAME_CAP 5000; 

int main(int argc, char* argv[])
{
	return 0;
}

CoreEngine::CoreEngine()
{
	game_ = new Game();
	RenderUtility::GLInitialize();
	is_running_ = false;
}

void CoreEngine::Start()
{
	if (is_running_)
		return;

	Run();
}

void CoreEngine::Stop()
{
	if (!is_running_)
		return;

	is_running_ = false;
}

void CoreEngine::Run()
{
	is_running_ = true;

	int frames = 0;

	double last_time = Time::GetTime();
	double unprocessed_time = 0;
	double frame_counter = 0;

	double frame_time = 1.0 / FRAME_CAP;
	
	while (is_running_)
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

			if (Window::CloseRequested())
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
	Window::Render();
}

void CoreEngine::Destroy()
{
	Window::Destroy();
}