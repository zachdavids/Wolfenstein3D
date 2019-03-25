#pragma once

#include <bitset>

class Node
{
public:

	enum Option : const int
	{
		Location = 0,
		Door = 1,
		Enemy = 2,
		Medkit = 3,
		Endpoint = 4
	};

	void SetFlag(std::bitset<5> flag) { flag_ = flag; };
	void SetOption(Option option) { flag_.flip(option); }
	bool IsType(Option option) const { return flag_.test(option); }
	std::bitset<5> GetFlag() { return flag_; }

private:
	
	std::bitset<5> flag_;
};