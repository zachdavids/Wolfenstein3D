#include "Door.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

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
}

void Door::Render()
{
	Shader* shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	shader->Bind();
	shader->SetMat4("transform", transform_->GetModelProjection());
	ResourceManager::Get()->GetResource<Texture>("DoorTile")->Bind();
	ResourceManager::Get()->GetResource<Mesh>("Door")->Draw();
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