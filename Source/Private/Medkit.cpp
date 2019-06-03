#include "Medkit.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"

const float LENGTH = 1.0f;
const float HEIGHT = 1.0f;
const float SCALE = 0.2f;

const int HEAL_AMOUNT = 30;

const float PICKUP_DISTANCE = 0.75f;

const int NUM_TEXTURES_X = 1;
const int NUM_TEXTURES_Y = 1;

Medkit::Medkit(glm::vec3 position)
{
	eaten_ = false;
	position_ = position;

	transform_ = new Transform();
	transform_->SetTranslation(position_);
	transform_->SetScale(glm::vec3(SCALE, SCALE, SCALE));
	transform_->SetCamera(Player::GetCamera());
}

void Medkit::Update()
{
	glm::vec3 camera_direction(transform_->GetCamera()->GetPosition().x - transform_->GetTranslation().x, transform_->GetCamera()->GetPosition().y, transform_->GetCamera()->GetPosition().z - transform_->GetTranslation().z);
	float camera_angle = -atanf(camera_direction.z / camera_direction.x) + (90.0f * glm::pi<float>() / 180.0f);

	if (camera_direction.x > 0) {
		camera_angle += glm::pi<float>();
	}
	else {
	}

	transform_->SetRotation(0, camera_angle, 0);

	if (glm::length(camera_direction) < PICKUP_DISTANCE) {
		//audio_->PlayMedkit();
		Player::Damage(-HEAL_AMOUNT);
		eaten_ = true;
	}
}

void Medkit::Render()
{
	Shader* shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	shader->Bind();
	shader->SetMat4("transform", transform_->GetModelProjection());
	ResourceManager::Get()->GetResource<Texture>("Medkit")->Bind();
	ResourceManager::Get()->GetResource<Mesh>("Billboard")->Draw();
}