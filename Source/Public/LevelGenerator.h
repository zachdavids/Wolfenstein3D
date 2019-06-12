#pragma once

#include "Node.h"

#include <vector>
#include <GLM/vec2.hpp>
#include <sol/sol.hpp>

class LevelGenerator
{
public:

	LevelGenerator(std::string const& filename);
	bool TryGenerate();
	//glm::ivec2 GetDimensions();
	//std::vector<Node>& GetNodes();

private:

	sol::state m_Lua;
	std::string m_FileName;
	//glm::ivec2 m_Dimensions;
	//std::vector<Node> m_Nodes;
};