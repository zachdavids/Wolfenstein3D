#pragma once

#include <iostream>
#include <vector>
#include <glm.hpp>
#include <pugixml.hpp>
#include "Node.h"

class XMLParser
{
public:

	XMLParser(std::string& filename);

	void SetDimensions(glm::vec2 dimensions) { dimensions_ = dimensions; };
	void SetNodes(std::vector<Node> nodes) { nodes_ = nodes; };

	glm::vec2 GetDimensions() const { return dimensions_; };
	std::vector<Node> const& GetNodes() const { return nodes_; };

	int GetNodeFlatIndex(int x, int y) { return (static_cast<int>(dimensions_.y) * y) + x; }

private:

	glm::vec2 dimensions_;
	std::vector<Node> nodes_;
	void ParseXMLFile(std::string& filename, pugi::xml_document& out_document) const;
	void ProcessLevelNode(pugi::xml_node& level_node);
	void InitializeNodeVector();
	void ProcessTileNode(pugi::xml_node& tile_node);
};