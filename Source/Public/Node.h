#pragma once

#include <bitset>

/*

*/

struct Node
{
	enum Type : const int
	{
		Tile,
		Door
	};

	int type;
	int ceiling;
	int floor;
	int top_wall;
	int bottom_wall;
	int left_wall;
	int right_wall;
	int enemy;
	int item;
};