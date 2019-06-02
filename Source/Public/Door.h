#ifndef DOOR_H
#define DOOR_H

#include "Mesh.h"
#include "Level.h"
#include "Transform.h"
#include "Player.h"
#include "TimeManager.h"
#include "AudioManager.h"

#include <GLM/gtx\compatibility.hpp>

class Door
{
public:
	
	Door(glm::vec3 position, glm::vec3 open_position, bool rotation);

	void Open();

	void Update();
	void Render();

	Mesh GetMesh() { return mesh_; };

	glm::vec3 GetDimensions();
	glm::vec3 GetTranslation() { return transform_->GetTranslation(); };

	glm::vec3 GetPosition() { return position_; };
	void SetPosition(glm::vec3 position) { position_ = position; };

private:

	bool is_open_;
	double open_start_, open_time_;
	double close_start_, close_time_;

	glm::vec3 position_;
	glm::vec3 open_position_;
	glm::vec3 close_position_;

	Mesh mesh_;
	Transform* transform_;

	void AddIndices(std::vector<unsigned int>& indices, int start, bool direction);
	void AddVertices(std::vector<Vertex>& vertices, std::string type, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords);
	std::vector<float> CalculateTextureCoords(int texture_number);
};

#endif;