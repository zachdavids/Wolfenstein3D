#include "CoreEngine.h"
#include "Window.h"
#include "Time.h"
#include "Game.h"
#include "Input.h"

#define FRAME_CAP 5000; 

#ifdef main
#undef main
#endif

int main(int argc, char *argv[])
{
	Window::Create(1280, 720, "Wolfenstein Clone");

	CoreEngine engine;
	engine.Start();

	return 0;
}

CoreEngine::CoreEngine() : game_(std::make_shared<Game>())
{
}

void CoreEngine::Start()
{
	if (is_running_) { return; }
	is_running_ = true;
	Run();
}

void CoreEngine::Stop()
{
	if (!is_running_) { return; }
	is_running_ = false;
}

void CoreEngine::Run() const
{
	int frames = 0;

	double start_time = 0;
	double passed_time = 0;
	double unprocessed_time = 0;
	double last_time = Time::GetTime();
	double frame_counter = 0;
	double frame_time = 1.0 / FRAME_CAP;

	bool render = false;
	while (is_running_)
	{
		render = false;
		start_time = Time::GetTime();
		passed_time = start_time - last_time;
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
			if (Window::CloseRequested()) 
			{
				//TODO MAKE CONST SOMEHOW
				//Stop(); 
			}

			render = true;

			Time::SetDelta(frame_time);
			Input::Update();
			game_->Input();
			game_->Update();
			//TODO CHECK THIS
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

void CoreEngine::Render() const
{
	Window::ClearScreen();
	game_->Render();
	Window::Render();
}

void CoreEngine::Destroy() const
{
	Window::Destroy();
}