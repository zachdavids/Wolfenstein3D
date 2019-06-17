#pragma once

struct Weapon
{
	bool bFireable;
	float range;
	double rate;
	double last_interval;
};