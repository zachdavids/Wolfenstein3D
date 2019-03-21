#pragma once

#include <chrono>
#include <iostream>

class Time
{
public:

	static double GetTime();
	static double GetDelta() { return delta_; };
	static void SetDelta(double delta) { delta_ = delta; };

private:

	static double delta_;
};