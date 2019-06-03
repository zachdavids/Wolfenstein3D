#include "Wall.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Player.h"

const float WALL_LENGTH = 0.125f;
const float WALL_WIDTH = 1.0f;

Wall::Wall(glm::vec3 const& position, glm::vec3 const& rotation, Type type) :
	m_Position(position)
{
	transform_.SetCamera(Player::GetCamera());
	transform_.SetRotation(rotation);
	transform_.SetTranslation(position);

	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Wall");

	switch (type)
	{
	case Type::kFloor:
		m_Texture = ResourceManager::Get()->GetResource<Texture>("DoorTile");
		break;
	case Type::kCeiling:
		m_Texture = ResourceManager::Get()->GetResource<Texture>("DoorTile");
		break;
	case Type::kWall:
		m_Texture = ResourceManager::Get()->GetResource<Texture>("DoorTile");
		break;
	}
}

void Wall::Render()
{
	Shader* shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	shader->Bind();
	shader->SetMat4("transform", transform_.GetModelProjection());
	ResourceManager::Get()->GetResource<Texture>("DoorTile")->Bind();
	m_Mesh->Draw();
}

glm::vec3 Wall::GetDimensions()
{
	if (transform_.GetRotation().y == glm::radians(-90.0f)) {
		return glm::vec3(WALL_LENGTH, 0, WALL_WIDTH);
	}
	else {
		return glm::vec3(WALL_WIDTH, 0, WALL_LENGTH);
	}
}