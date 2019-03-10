#include "Time.h"

double Time::delta_ = 0.0;

double Time::GetTime()
{
	auto beginningOfTime = std::chrono::high_resolution_clock::now().time_since_epoch();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(beginningOfTime).count();
	return 10 * 0.001;
}

double Time::GetDelta()
{
	return delta_;
}

void Time::SetDelta(double delta)
{
	delta_ = delta;
}
