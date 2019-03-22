#include "Door.h"
#include "Mesh.h"
#include "Audio.h"
#include "Time.h"
#include "Player.h"
#include "Transform.h"
#include "Level.h"

Door::Door(glm::vec3 position, Material* material, glm::vec3 open_position, bool rotation) :
	material_(material), position_(position), 
	open_position_(open_position), close_position_(position)
{
	audio_ = new Audio();

	shader_ = Level::GetShader();

	transform_ = new Transform();
	transform_->SetCamera(Player::GetCamera());
	transform_->SetTranslation(position_);

	if (rotation)
	{
		transform_->SetRotation(glm::vec3(0, glm::radians(-90.0f), 0));
	}

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	AddIndices(indices, vertices.size(), false);
	AddVertices(vertices, CalculateTextureCoords(27), glm::vec3(0, 0, 0), "Door", false);

	AddIndices(indices, vertices.size(), true);
	AddVertices(vertices, CalculateTextureCoords(0), glm::vec3(0, 0, 0), "Door", true);

	AddIndices(indices, vertices.size(), true);
	AddVertices(vertices, CalculateTextureCoords(27), glm::vec3(0, 0, door_length_), "Door", false);

	AddIndices(indices, vertices.size(), false);
	AddVertices(vertices, CalculateTextureCoords(0), glm::vec3(door_width_, 0, 0), "Door", true);

	mesh_.InitializeMesh(vertices, indices);
}

void Door::Open()
{
	if (is_open_) { return; }

	is_open_ = true;

	open_start_ = static_cast<float>(Time::GetTime());
	open_time_ = open_start_ + open_time_;
	close_start_ = open_time_ + delay_;
	close_time_ = close_start_ + close_time_;
}

void Door::Update()
{
	if (!is_open_) { return; }

	double time = Time::GetTime();
	if (time < open_time_) 
	{
		transform_->SetTranslation(glm::lerp(close_position_, open_position_, (float)(time - open_start_ / open_time_)));
		audio_->PlayDoorOpen();
	}
	else if (time < close_start_)
	{
		transform_->SetTranslation(open_position_);
	}
	else if (time < close_time_)
	{
		transform_->SetTranslation(glm::lerp(open_position_, close_position_, (float)(time - close_start_ / open_time_)));
		audio_->PlayDoorClose();
	}
	else
	{
		transform_->SetTranslation(close_position_);
		is_open_ = false;
	}
}

void Door::Render()
{
	shader_->UpdateUniforms(transform_->GetModelViewProjection(), material_);
	mesh_.Draw();
}

void Door::AddIndices(std::vector<unsigned int>& indices, int start, bool direction)
{
	if (direction) 
	{
		indices.push_back(start + 2);
		indices.push_back(start + 1);
		indices.push_back(start + 0);

		indices.push_back(start + 3);
		indices.push_back(start + 2);
		indices.push_back(start + 0);
	}
	else 
	{
		indices.push_back(start + 0);
		indices.push_back(start + 1);
		indices.push_back(start + 2);

		indices.push_back(start + 0);
		indices.push_back(start + 2);
		indices.push_back(start + 3);
	}
}

void Door::AddVertices(std::vector<Vertex>& vertices, std::vector<float>& texture_coords, glm::vec3 coords, std::string type, bool invert)
{
	if (type == "Door")
	{
		if (!invert) 
		{
			vertices.push_back(Vertex{ coords, glm::vec2(texture_coords[0], texture_coords[2]) });
			vertices.push_back(Vertex{ glm::vec3(coords.x, door_height_, coords.z), glm::vec2(texture_coords[0], texture_coords[3]) });
			vertices.push_back(Vertex{ glm::vec3(door_width_, door_height_, coords.z), glm::vec2(texture_coords[1], texture_coords[3]) });
			vertices.push_back(Vertex{ glm::vec3(door_width_, coords.y, coords.z), glm::vec2(texture_coords[1], texture_coords[2]) });
		}
		else 
		{
			vertices.push_back(Vertex{ coords, glm::vec2(0, 0) });
			vertices.push_back(Vertex{ glm::vec3(coords.x, door_height_, coords.z), glm::vec2(0, 0) });
			vertices.push_back(Vertex{ glm::vec3(coords.x, door_height_, door_length_), glm::vec2(0, 0) });
			vertices.push_back(Vertex{ glm::vec3(coords.x, coords.y, door_length_), glm::vec2(0, 0) });
		}
	}
}

std::vector<float> Door::CalculateTextureCoords(int texture_number)
{
	float texture_x = static_cast<float>(texture_number % texture_width_);
	float texture_y = static_cast<float>(texture_number / texture_width_);
	
	std::vector<float> texture_coords;
	texture_coords.push_back((1.0f / texture_width_) + (1.0f / texture_width_) * texture_x);
	texture_coords.push_back((texture_coords[0] - (1.0f / texture_width_)));
	texture_coords.push_back((1.0f / texture_height_) + (1.0f / texture_height_) * texture_y);
	texture_coords.push_back((texture_coords[2] - (1.0f / texture_height_)));

	return texture_coords;
}

glm::vec3 Door::GetDimensions()
{
	if (transform_->GetRotation().y == glm::radians(-90.0f)) 
	{
		return glm::vec3(door_length_, 0, door_width_);
	}
	else 
	{
		return glm::vec3(door_width_, 0, door_length_);
	}
}