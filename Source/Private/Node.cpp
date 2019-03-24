#include "Node.h"

Node::Node(glm::vec3 position)
{
	position_ = position;
	type_ = "";
}

Node::Node(glm::vec3 position, std::string type)
{
	position_ = position;
	type_ = type;
}