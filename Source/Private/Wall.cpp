#include "Wall.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Player.h"

Wall::Wall(glm::vec3 const& position, glm::vec3 const& rotation, Type type) :
	m_Position(position)
{
	transform_.SetCamera(Player::GetCamera());
	transform_.SetRotation(rotation);
	transform_.SetTranslation(position);

	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Wall");
	m_Shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");

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
	m_Shader->Bind();
	m_Shader->SetMat4("transform", transform_.GetModelProjection());
	m_Texture->Bind();
	m_Mesh->Draw();
}