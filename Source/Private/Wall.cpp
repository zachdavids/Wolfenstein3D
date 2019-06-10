#include "Wall.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

Wall::Wall(glm::vec3 const& position, glm::vec3 const& rotation, Type type)
{
	SetRotation(rotation);
	SetPosition(position);

	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Wall");
	m_Shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");

	switch (type)
	{
	case Type::kFloor:
		m_Texture = ResourceManager::Get()->GetResource<Texture>("FloorTile");
		break;
	case Type::kCeiling:
		m_Texture = ResourceManager::Get()->GetResource<Texture>("CeilingTile");
		break;
	case Type::kWall:
		m_Texture = ResourceManager::Get()->GetResource<Texture>("WallTile");
		break;
	}
}

void Wall::Render()
{
	m_Shader->Bind();
	m_Shader->SetMat4("model", GetModelMatrix());
	m_Texture->Bind();
	m_Mesh->Draw();
}