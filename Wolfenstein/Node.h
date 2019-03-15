#pragma once

#include <glm.hpp>

class Node
{
public:

	enum class Flag : unsigned char
	{
		kWall = 0b0000'0000,
		kLocation = 0b0000'0001,
		kDoor = 0b0000'0010,
		kEnemy = 0b0000'0100,
		kMedkit = 0b0000'1000,
		kEndpoint = 0b0001'0000
	};

	friend Flag operator|(Flag a, Flag b)
	{
		return static_cast<Flag>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
	}

	friend Flag operator&(Flag a, Flag b)
	{
		return static_cast<Flag>(static_cast<unsigned char>(a) & static_cast<unsigned char>(b));
	}

	friend Flag& operator|=(Flag& a, Flag b)
	{
		return a = a | b;
	}

	Node(Node::Flag flag);
	Node::Flag GetFlag() { return flag_; };
	void SetFlag(Node::Flag flag) { flag_ |= flag; };
	bool IsType(Node::Flag flag) { return static_cast<bool>(flag_ & flag); }

private:
	
	Node::Flag flag_;
};