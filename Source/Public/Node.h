#pragma once

#include <bitset>

struct Node
{
	enum NodeType : const int
	{
		Location,
		Door,
		Enemy,
		Medkit,
		Endpoint
	};

	std::bitset<5> m_Node;
};