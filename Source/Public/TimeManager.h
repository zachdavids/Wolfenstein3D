#pragma once

class TimeManager
{
public:

	static double GetTime();
	static double GetDelta();
	static void SetDelta(double delta);

private:

	static double delta_;
};