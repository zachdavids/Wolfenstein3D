#ifndef NODE_H
#define NODE_H

#include <glm/glm.hpp>
#include <string>

class Node
{
public:

	Node(glm::vec3 position);
	Node(glm::vec3 position, std::string type);

	std::string GetType() { return type_; };
	void SetType(std::string type) { type_ = type; };

	glm::vec3 GetPosition() { return position_; };
	void SetPosition(glm::vec3 position) { position_ = position; };

private:
	
	std::string type_;
	glm::vec3 position_;
};

#endif;