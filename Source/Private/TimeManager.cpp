#include "TimeManager.h"

double TimeManager::delta_ = 0.0;

double TimeManager::GetTime()
{
	auto beginningOfTime = std::chrono::high_resolution_clock::now().time_since_epoch();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(beginningOfTime).count();
	return ms * 0.001;
}

double TimeManager::GetDelta()
{
	return delta_;
}

void TimeManager::SetDelta(double delta)
{
	delta_ = delta;
}
