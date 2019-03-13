#pragma once

#include "Camera.h"
#include "Level.h"
#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Shader.h"
#include "Audio.h"

class Player
{
public:

	Player(glm::vec3 position, int yaw, int pitch);

	static void Damage(int damage_points);

	void Input();
	void Update();
	void Render();

	static int GetHealth();

	static Camera* GetCamera();

private:

	bool shot_;

	glm::vec3 old_position_;
	glm::vec3 new_position_;
	glm::vec3 collision_vector_;
	glm::vec3 movement_vector_;

	Material* material_;
	Material* material_2;
	Material* material_3;
	Material* material_4;
	Mesh mesh_;
	Transform* transform_;
	Transform* transform_2;
	Transform* transform_3;
	Transform* transform_4;
	Shader* shader_;
	Audio* audio_;

	std::vector<Texture*> animations_;
	std::vector<Texture*> animations_2;

	void AddIndices(std::vector<unsigned int>& indices, int start, bool direction);
	void AddVertices(std::vector<Vertex>& vertices, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords);
	std::vector<float> CalculateTextureCoords(int texture_number);
};