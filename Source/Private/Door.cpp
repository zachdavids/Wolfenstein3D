#include "Door.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"

const float DOOR_LENGTH = 0.125f;
const float DOOR_WIDTH = 1.0f;
const float DOOR_HEIGHT = 1.0f;

const float TIME_TO_OPEN = 1.0f;
const float DELAY = 3.0f;
const float TIME_TO_CLOSE = 1.0f;

const int NUM_TEXTURES_X = 6;
const int NUM_TEXTURES_Y = 19;

Door::Door(glm::vec3 position, glm::vec3 open_position, bool rotation)
{
	is_open_ = false;

	position_ = position;
	open_position_ = open_position;
	close_position_ = position;

	transform_ = new Transform();
	transform_->SetCamera(Player::GetCamera());

	if (rotation) {
		transform_->SetRotation(glm::vec3(0, glm::radians(-90.0f), 0));
		//TODO:: OFFSET
		transform_->SetTranslation(position_);
	}
	else {
		//TODO:: OFFSET
		transform_->SetTranslation(position_);
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	AddIndices(indices, vertices.size(), false);
	AddVertices(vertices, "Door", false, 0, 0, 0, CalculateTextureCoords(27));

	AddIndices(indices, vertices.size(), true);
	AddVertices(vertices, "Door", true, 0, 0, 0, CalculateTextureCoords(0));

	AddIndices(indices, vertices.size(), true);
	AddVertices(vertices, "Door", false, 0, 0, DOOR_LENGTH, CalculateTextureCoords(27));

	AddIndices(indices, vertices.size(), false);
	AddVertices(vertices, "Door", true, DOOR_WIDTH, 0, 0, CalculateTextureCoords(0));

	mesh_.InitializeMesh(vertices, indices);
}

void Door::Open()
{
	if (!is_open_) {
		is_open_ = true;

		open_start_ = TimeManager::GetTime();
		open_time_ = open_start_ + TIME_TO_OPEN;
		close_start_ = open_time_ + DELAY;
		close_time_ = close_start_ + TIME_TO_CLOSE;
	}
	else {
	}
}

void Door::Update()
{
	if (is_open_) {
		double time = TimeManager::GetTime();
		if (time < open_time_) {
			transform_->SetTranslation(glm::lerp(close_position_, open_position_, (float)(time - open_start_ / TIME_TO_OPEN)));
			//audio_->PlayDoorOpen();
		}
		else if (time < close_start_) {
			transform_->SetTranslation(open_position_);
		}
		else if (time < close_time_) {
			transform_->SetTranslation(glm::lerp(open_position_, close_position_, (float)(time - close_start_ / TIME_TO_OPEN)));
			//audio_->PlayDoorClose();
		}
		else {
			transform_->SetTranslation(close_position_);
			is_open_ = false;
		}
	}
	else {
	}
}

void Door::Render()
{
	Shader* shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	shader->Bind();
	shader->SetMat4("transform", transform_->GetModelProjection());
	ResourceManager::Get()->GetResource<Texture>("TileTextures")->Bind();
	mesh_.Draw();
}

void Door::AddIndices(std::vector<unsigned int>& indices, int start, bool direction)
{
	if (direction) {
		indices.push_back(start + 2);
		indices.push_back(start + 1);
		indices.push_back(start + 0);

		indices.push_back(start + 3);
		indices.push_back(start + 2);
		indices.push_back(start + 0);
	}
	else {
		indices.push_back(start + 0);
		indices.push_back(start + 1);
		indices.push_back(start + 2);

		indices.push_back(start + 0);
		indices.push_back(start + 2);
		indices.push_back(start + 3);
	}
}

void Door::AddVertices(std::vector<Vertex>& vertices, std::string type, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords)
{
	if (type == "Door")
	{
		if (!invert) {
			vertices.push_back(Vertex{ glm::vec3(x_coord, y_coord, z_coord), glm::vec2(texture_coords[0], texture_coords[2]) });
			vertices.push_back(Vertex{ glm::vec3(x_coord, DOOR_HEIGHT, z_coord), glm::vec2(texture_coords[0], texture_coords[3]) });
			vertices.push_back(Vertex{ glm::vec3(DOOR_WIDTH, DOOR_HEIGHT, z_coord), glm::vec2(texture_coords[1], texture_coords[3]) });
			vertices.push_back(Vertex{ glm::vec3(DOOR_WIDTH, y_coord, z_coord), glm::vec2(texture_coords[1], texture_coords[2]) });
		}
		else {
			vertices.push_back(Vertex{ glm::vec3(x_coord, y_coord, z_coord), glm::vec2(0, 0) });
			vertices.push_back(Vertex{ glm::vec3(x_coord, DOOR_HEIGHT, z_coord), glm::vec2(0, 0) });
			vertices.push_back(Vertex{ glm::vec3(x_coord, DOOR_HEIGHT, DOOR_LENGTH), glm::vec2(0, 0) });
			vertices.push_back(Vertex{ glm::vec3(x_coord, y_coord, DOOR_LENGTH), glm::vec2(0, 0) });
		}
	}
	else {
	}
}

std::vector<float> Door::CalculateTextureCoords(int texture_number)
{
	float texture_x = (float)(texture_number % NUM_TEXTURES_X);
	float texture_y = (float)(texture_number / NUM_TEXTURES_X);
	std::vector<float> texture_coords;

	texture_coords.push_back((1.0f / NUM_TEXTURES_X) + (1.0f / NUM_TEXTURES_X) * texture_x);
	texture_coords.push_back((texture_coords[0] - (1.0f / NUM_TEXTURES_X)));
	texture_coords.push_back((1.0f / NUM_TEXTURES_Y) + (1.0f / NUM_TEXTURES_Y) * texture_y);
	texture_coords.push_back((texture_coords[2] - (1.0f / NUM_TEXTURES_Y)));

	return texture_coords;
}

glm::vec3 Door::GetDimensions()
{
	if (transform_->GetRotation().y == glm::radians(-90.0f)) {
		return glm::vec3(DOOR_LENGTH, 0, DOOR_WIDTH);
	}
	else {
		return glm::vec3(DOOR_WIDTH, 0, DOOR_LENGTH);
	}
}