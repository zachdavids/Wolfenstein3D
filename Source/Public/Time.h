#pragma once

#include <chrono>
#include <iostream>

class Time
{
public:

	static double GetTime();
	static double GetDelta();
	static void SetDelta(double delta);

private:

	static double delta_;
};