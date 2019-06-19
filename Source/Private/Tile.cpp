#include "Tile.h"
#include "ResourceManager.h"

Tile::Tile(glm::vec3 const& position, glm::vec3 const& rotation, int t_id, Mesh* mesh)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Tid = t_id;
	m_Mesh = mesh;
	m_Shader = ResourceManager::Get()->GetResource<Shader>("TileShader");
	m_Texture = ResourceManager::Get()->GetResource<TextureArray>("SpriteSheet");
}