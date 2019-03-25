#pragma once

#include "Node.h"

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <pugixml/pugixml.hpp>

class XMLParser
{
public:

	XMLParser(std::string const& filename);

	glm::vec2 GetDimensions() const { return dimensions_; };
	std::vector<Node> const& GetNodes() const { return nodes_; };

	int GetFlatIndex(int x, int y) const { return (static_cast<int>(dimensions_.y) * y) + x; }

private:

	glm::vec2 dimensions_;
	std::vector<Node> nodes_;

	void ParseXMLFile(std::string const& filename, pugi::xml_document& out_document) const;
	void ProcessLevelNode(pugi::xml_node const& level_node);
	void InitializeNodeVector();
	void ProcessTileNode(pugi::xml_node const& tile_node);
};