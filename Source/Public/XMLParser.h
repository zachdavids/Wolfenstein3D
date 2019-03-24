#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <iostream>
#include <vector>

#include <pugixml/pugixml.hpp>
#include <GLM/glm.hpp>
#include "Node.h"

class XMLParser
{
public:

	XMLParser() {};
	XMLParser(std::string filename);

	glm::vec2 GetDimensions() { return dimensions_; };
	void SetDimenions(glm::vec2 dimensions) { dimensions_ = dimensions; };

	std::vector<Node> GetNodes() { return nodes_; };
	void SetNodes(std::vector<Node> nodes) { nodes_ = nodes; };

	std::vector<Node> GetDoorNodes() { return door_nodes_; };
	std::vector<Node> GetEnemyNodes() { return enemy_nodes_; };
	std::vector<Node> GetMedkitNodes() { return medkit_nodes_; };
	std::vector<Node> GetEndPointNodes() { return endpoint_nodes_; };

private:

	glm::vec2 dimensions_;
	std::vector<Node> nodes_;
	std::vector<Node> door_nodes_;
	std::vector<Node> enemy_nodes_;
	std::vector<Node> medkit_nodes_;
	std::vector<Node> endpoint_nodes_;
};

#endif;