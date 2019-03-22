#pragma once

#include <gtx\compatibility.hpp>

#include "Door.h"
#include "Mesh.h"
#include "Audio.h"
#include "Time.h"
#include "Player.h"
#include "Transform.h"
#include "Level.h"

class Door
{
public:
	
	//todo const
	Door(glm::vec3 position, Material* material, glm::vec3 open_position, bool rotation = false);

	void Open();

	void Update();
	void Render();

	Mesh GetMesh() { return mesh_; };

	glm::vec3 GetDimensions();
	glm::vec3 GetTranslation() { return transform_->GetTranslation(); };

	glm::vec3 GetPosition() { return position_; };
	void SetPosition(glm::vec3 position) { position_ = position; };

private:

	bool is_open_ = false;

	int const texture_width_ = 6;
	int const texture_height_ = 19;

	float const door_length_ = 0.125f;
	float const door_width_ = 1.0f;
	float const door_height_ = 1.0f;

	float open_start_ = 0;
	float close_start_ = 0;
	float open_time_ = 1.0f;
	float const delay_ = 3.0f;
	float close_time_ = 1.0f;

	glm::vec3 position_;
	glm::vec3 open_position_;
	glm::vec3 close_position_;

	//todo smart ptrs
	Audio* audio_;
	Mesh mesh_;
	Transform* transform_;
	Shader* shader_;
	Material* material_;

	void AddIndices(std::vector<unsigned int>& indices, int start, bool direction);
	void AddVertices(std::vector<Vertex>& vertices, std::vector<float>& texture_coords, glm::vec3 coords, std::string type, bool invert);
	std::vector<float> CalculateTextureCoords(int texture_number);
};