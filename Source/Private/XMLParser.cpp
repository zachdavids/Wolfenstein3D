#include "XMLParser.h"

#include <iostream>

XMLParser::XMLParser(std::string const& filename) : m_FileName(filename)
{
}

bool XMLParser::TryParse()
{
	pugi::xml_document level_document;
	pugi::xml_parse_result result = level_document.load_file(("Resources/Levels/" + m_FileName).c_str());

	if (!result.description())
	{
		return false;
	}
	else
	{
		ParseLevel(level_document.child("Level"));
	}

	return true;
}

void XMLParser::ParseLevel(pugi::xml_node const& level_node)
{
	std::string dimensions_string = level_node.child_value("Dimensions");
	m_Dimensions.x = std::stoi(dimensions_string.substr(0, dimensions_string.find(",")));
	m_Dimensions.y = std::stoi(dimensions_string.substr(dimensions_string.find(",") + 1));

	for (int i = 0; i != m_Dimensions.x * m_Dimensions.y; ++i)
	{
		m_Nodes.emplace_back(Node());
	}

	ParseTiles(level_node);
}

void XMLParser::ParseTiles(pugi::xml_node const& level_node)
{
	for (pugi::xml_node tile = level_node.child("Node"); tile; tile = tile.next_sibling("Node"))
	{
		std::string location_string = tile.child_value("Location");
		if (location_string != "")
		{
			int col = std::stoi(location_string.substr(0, location_string.find(",")));
			int row = std::stoi(location_string.substr(location_string.find(",") + 1));

			Node new_node;
			new_node.m_Node.flip(Node::NodeType::Location);

			if (std::string(tile.child_value("Door")) != "")
			{
				new_node.m_Node.flip(Node::NodeType::Door);
			}
			if (std::string(tile.child_value("Enemy")) != "")
			{
				new_node.m_Node.flip(Node::NodeType::Enemy);
			}
			if (std::string(tile.child_value("Medkit")) != "")
			{
				new_node.m_Node.flip(Node::NodeType::Medkit);
			}
			if (std::string(tile.child_value("Endpoint")) != "")
			{
				new_node.m_Node.flip(Node::NodeType::Endpoint);
			}
			m_Nodes[m_Dimensions.y * col + row] = new_node;
		}
	}
}

std::vector<Node>& XMLParser::GetNodes()
{
	return m_Nodes;
}

glm::ivec2 XMLParser::GetDimensions()
{
	return m_Dimensions;
}