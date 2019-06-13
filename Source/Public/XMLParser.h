#pragma once

#include "Node.h"

#include <vector>
#include <GLM/vec2.hpp>
#include <pugixml/pugixml.hpp>

class XMLParser
{
public:

	XMLParser(std::string const& filename);
	bool TryParse();
	glm::ivec2 GetDimensions();
	std::vector<Node>& GetNodes();

private:

	std::string m_FileName;
	glm::ivec2 m_Dimensions;
	std::vector<Node> m_Nodes;

	void ParseLevel(pugi::xml_node const& level_node);
	void ParseTiles(pugi::xml_node const& level_node);
};