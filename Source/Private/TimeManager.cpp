#include "TimeManager.h"

#include <chrono>
#include <iostream>

double TimeManager::m_Delta = 0.0;

double TimeManager::GetTime()
{
	auto beginningOfTime = std::chrono::high_resolution_clock::now().time_since_epoch();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(beginningOfTime).count();
	return ms * 0.001;
}

double TimeManager::GetDelta()
{
	return m_Delta;
}

void TimeManager::SetDelta(double delta)
{
	m_Delta = delta;
}
