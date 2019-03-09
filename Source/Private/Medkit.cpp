#include "Medkit.h"

const float LENGTH = 1.0f;
const float HEIGHT = 1.0f;
const float SCALE = 0.2f;

const int HEAL_AMOUNT = 30.0f;

const float PICKUP_DISTANCE = 0.75f;

const int NUM_TEXTURES_X = 1;
const int NUM_TEXTURES_Y = 1;

Medkit::Medkit(glm::vec3 position)
{
	eaten_ = false;
	audio_ = new Audio();
	position_ = position;

	transform_ = new Transform();
	transform_->SetTranslation(position_);
	transform_->SetScale(glm::vec3(SCALE, SCALE, SCALE));
	transform_->SetCamera(Player::GetCamera());

	material_ = new Material(new Texture("Textures/media.png"));

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	AddIndices(indices, vertices.size(), false);
	AddVertices(vertices, false, 0, 0, 0, CalculateTextureCoords(27));
	mesh_.InitializeMesh(vertices, indices);
}

void Medkit::Update()
{
	glm::vec3 camera_direction(transform_->GetCamera()->GetPosition().x - transform_->GetTranslation().x, transform_->GetCamera()->GetPosition().y, transform_->GetCamera()->GetPosition().z - transform_->GetTranslation().z);
	float camera_angle = -atanf(camera_direction.z / camera_direction.x) + (90.0f * M_PI / 180.0f);

	if (camera_direction.x > 0) {
		camera_angle += M_PI;
	}
	else {
	}

	transform_->SetRotation(0, camera_angle, 0);

	if (glm::length(camera_direction) < PICKUP_DISTANCE) {
		audio_->PlayMedkit();
		Player::Damage(-HEAL_AMOUNT);
		eaten_ = true;
	}
}

void Medkit::Render()
{
	shader_ = Level::GetShader();
	shader_->UpdateUniforms(transform_->GetModelProjection(), material_);
	mesh_.Draw();
}

void Medkit::AddIndices(std::vector<unsigned int>& indices, int start, bool direction)
{
	indices.push_back(start + 0);
	indices.push_back(start + 1);
	indices.push_back(start + 2);

	indices.push_back(start + 0);
	indices.push_back(start + 2);
	indices.push_back(start + 3);

}

void Medkit::AddVertices(std::vector<Vertex>& vertices, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords)
{
	vertices.push_back(Vertex(glm::vec3(-LENGTH / 2, y_coord, z_coord), glm::vec2(texture_coords[0], texture_coords[2])));
	vertices.push_back(Vertex(glm::vec3(-LENGTH / 2, HEIGHT, z_coord), glm::vec2(texture_coords[0], texture_coords[3])));
	vertices.push_back(Vertex(glm::vec3(LENGTH / 2, HEIGHT, z_coord), glm::vec2(texture_coords[1], texture_coords[3])));
	vertices.push_back(Vertex(glm::vec3(LENGTH / 2, y_coord, z_coord), glm::vec2(texture_coords[1], texture_coords[2])));
}

std::vector<float> Medkit::CalculateTextureCoords(int texture_number)
{
	float texture_x = texture_number % NUM_TEXTURES_X;
	float texture_y = texture_number / NUM_TEXTURES_X;
	std::vector<float> texture_coords;

	texture_coords.push_back((1.0f / NUM_TEXTURES_X) + (1.0f / NUM_TEXTURES_X) * texture_x);
	texture_coords.push_back((texture_coords[0] - (1.0f / NUM_TEXTURES_X)));
	texture_coords.push_back((1.0f / NUM_TEXTURES_Y) + (1.0f / NUM_TEXTURES_Y) * texture_y);
	texture_coords.push_back((texture_coords[2] - (1.0f / NUM_TEXTURES_Y)));

	return texture_coords;
}