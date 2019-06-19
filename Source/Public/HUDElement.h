#pragma once

#include <GLM/vec3.hpp>

class Mesh;
class Texture;

struct HUDElement
{
	float alpha;
	glm::vec3 position;
	glm::vec3 scale;
	Mesh* mesh;
	Texture* texture;
};