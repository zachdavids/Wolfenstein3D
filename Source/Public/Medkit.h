#ifndef MEDKIT_H
#define MEDKIT_H

#include "Level.h"
#include "Mesh.h"
#include "Transform.h"
#include "AudioManager.h"

class Medkit
{
public:

	Medkit(glm::vec3 position);

	void Update();
	void Render();
	bool GetEaten() { return eaten_; };

private:

	bool eaten_;

	glm::vec3 position_;
	Transform* transform_;
	Mesh mesh_;

	void AddIndices(std::vector<unsigned int>& indices, int start, bool direction);
	void AddVertices(std::vector<Vertex>& vertices, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords);
	std::vector<float> CalculateTextureCoords(int texture_number);
};

#endif;