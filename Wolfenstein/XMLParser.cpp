#include "XMLParser.h"

XMLParser::XMLParser(std::string& filename)
{
	pugi::xml_document document;
	ParseXMLFile(filename, document);
	for (pugi::xml_node level = document.child("Level"); level; level = level.next_sibling("Level"))
	{
		ProcessLevelNode(level);
		InitializeNodeVector();
		for (pugi::xml_node node = level.child("Node"); node; node = node.next_sibling("Node"))
		{
			ProcessTileNode(node);
		}
	}
}

void XMLParser::ParseXMLFile(std::string& filename, pugi::xml_document& out_document) const
{
	pugi::xml_parse_result result = out_document.load_file(filename.c_str());
	assert(result);
}

void XMLParser::ProcessLevelNode(pugi::xml_node& level_node)
{
	std::string dimension = level_node.child_value("Dimensions");
	dimensions_.x = std::stof(dimension.substr(0, dimension.find(",")));
	dimensions_.y = std::stof(dimension.substr(dimension.find(",") + 1));
}

void XMLParser::InitializeNodeVector()
{
	for (int i = 0; i != dimensions_.x * dimensions_.y; i++)
	{
		nodes_.push_back(Node(Node::Flag::kWall));
	}
}

void XMLParser::ProcessTileNode(pugi::xml_node& tile_node)
{
	std::string location_string = tile_node.child_value("Location");
	if (location_string.find(",") != std::string::npos)
	{
		int node_x = std::stoi(location_string.substr(0, location_string.find(",")));
		int node_z = std::stoi(location_string.substr(location_string.find(",") + 1));

		Node::Flag node_flag = Node::Flag::kLocation;
		if (tile_node.child_value("Door") != "")
		{
			node_flag |= Node::Flag::kDoor;
		}
		if (tile_node.child_value("Enemy") != "")
		{
			node_flag |= Node::Flag::kEnemy;
		}
		if (tile_node.child_value("Medkit") != "")
		{
			node_flag |= Node::Flag::kMedkit;
		}
		if (tile_node.child_value("Endpoint") != "")
		{
			node_flag |= Node::Flag::kEndpoint;
		}
		nodes_[GetNodeFlatIndex(node_x, node_z)].SetFlag(node_flag);
	}
}