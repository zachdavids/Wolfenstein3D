#pragma once

#include "Mapdata.h"

#include <nlohmann/json.hpp>

class LevelGenerator
{
public:

	LevelGenerator() = default;
	Mapdata Generate(std::string const& filename);

private:

	static const std::string s_Directory;
	static const int s_MapSize;
	glm::vec3 CalcPos(int index);
	void GenerateGeometry(nlohmann::json& layer, Mapdata& map);
	void GenerateObjects(nlohmann::json& layer, Mapdata& map);
};

