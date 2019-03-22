#pragma once

#include <iostream>

class Game;

class CoreEngine
{
public:

	CoreEngine();

	void Start();
	void Stop();
	void Run() const;
	void Render() const;
	void Destroy() const;

private:

	bool is_running_ = false;
	std::shared_ptr<Game> game_;
};