#pragma once

#include "Mapdata.h"

#include <nlohmann/json.hpp>

class LevelGenerator
{
public:

	LevelGenerator() = default;
	Mapdata Generate(std::string const& filename);
	static constexpr auto s_Directory = "Resources/Levels/";
	static constexpr int s_MapSize = 64;

private:

	glm::vec3 CalcPos(int index);
	void GenerateGeometry(nlohmann::json& layer, Mapdata& map);
	void GenerateObjects(nlohmann::json& layer, Mapdata& map);
};

