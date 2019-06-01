#ifndef VERTEX_H
#define VERTEX_H

#include <GLM/glm.hpp>

class Vertex
{
public:

	Vertex(glm::vec3 position);
	Vertex(glm::vec3 position, glm::vec2 texture_coord);
	Vertex(glm::vec3 position, glm::vec2 texture_coord, glm::vec3 normal);

	glm::vec3 GetPosition() { return position_; };
	void SetPosition(glm::vec3 position) { position_ = position; };

	glm::vec2 GetTextureCoord() { return texture_coord_; };
	void SetTextureCoord(glm::vec2 texture_coord) { texture_coord_ = texture_coord; };

	glm::vec3 GetNormal() { return normal_; };
	void SetNormal(glm::vec3 normal) { normal_ = normal; };

private:

	glm::vec3 position_;
	glm::vec2 texture_coord_;
	glm::vec3 normal_;
};

#endif;