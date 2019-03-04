#include "XMLParser.h"

XMLParser::XMLParser(std::string filename)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filename.c_str());
	std::cout << "Parsing " << filename << "... ";
	if (result.description()) {
		std::cout << "success" << std::endl;
	}
	else {
		exit(1);
	}

	for (pugi::xml_node level = doc.child("Level"); level; level = level.next_sibling("Level"))
	{
		// Dimensions
		//std::cout << "Dimensions: " << "\n";
		std::string dimensions_string = level.child_value("Dimensions");
		unsigned int dimensions_x = std::stoul(dimensions_string.substr(0, dimensions_string.find(",")));
		unsigned int dimensions_y = std::stoul(dimensions_string.substr(dimensions_string.find(",") + 1));
		SetDimenions(glm::vec2(dimensions_x, dimensions_y));
		for (unsigned int i = 0; i < dimensions_x; i++) {
			for (unsigned int j = 0; j < dimensions_y; j++) {
				nodes_.push_back(Node(glm::vec3(i, 0, j), "Wall"));
				door_nodes_.push_back(Node(glm::vec3(i, 0, j), ""));
				enemy_nodes_.push_back(Node(glm::vec3(i, 0, j), ""));
				medkit_nodes_.push_back(Node(glm::vec3(i, 0, j), ""));
				endpoint_nodes_.push_back(Node(glm::vec3(i, 0, j), ""));
			}
		}

		// Nodes
		//std::cout << "Nodes: " << "\n";
		for (pugi::xml_node node = level.child("Node"); node; node = node.next_sibling("Node"))
		{
			std::string location_string = node.child_value("Location");
			std::string door_string = node.child_value("Door");
			std::string enemy_string = node.child_value("Enemy");
			std::string medkit_string = node.child_value("Medkit");
			std::string endpoint_string = node.child_value("Endpoint");

			if (location_string.find(",") != std::string::npos) {
				unsigned int node_x = std::stoul(location_string.substr(0, location_string.find(",")));
				unsigned int node_z = std::stoul(location_string.substr(location_string.find(",") + 1));
				nodes_[node_x * GetDimensions().y + node_z].SetType("Location");

				if (door_string != "") {
					door_nodes_[node_x * GetDimensions().y + node_z].SetType("Door");
				}
				if (enemy_string != "") {
					enemy_nodes_[node_x * GetDimensions().y + node_z].SetType("Enemy");
				}
				if (medkit_string != "") {
					medkit_nodes_[node_x * GetDimensions().y + node_z].SetType("Medkit");
				}
				if (endpoint_string != "") {
					endpoint_nodes_[node_x * GetDimensions().y + node_z].SetType("Endpoint");
				}
			}
		}
	}
}