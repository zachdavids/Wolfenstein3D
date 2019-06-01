#include "Vertex.h"

Vertex::Vertex(glm::vec3 position)
{
	position_ = position;
}

Vertex::Vertex(glm::vec3 position, glm::vec2 texture_coord)
{
	position_ = position;
	texture_coord_ = texture_coord;
}

Vertex::Vertex(glm::vec3 position, glm::vec2 texture_coord, glm::vec3 normal)
{
	position_ = position;
	texture_coord_ = texture_coord;
	normal_ = normal;
}