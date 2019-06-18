#include "Tile.h"
#include "ResourceManager.h"

Tile::Tile(glm::vec3 const& position, glm::vec3 const& rotation, int t_id, Mesh* mesh) :
	Actor(
		position,
		rotation, 
		t_id,
		mesh,
		ResourceManager::Get()->GetResource<Shader>("TileShader"),
		ResourceManager::Get()->GetResource<TextureArray>("SpriteSheet")
	)
{
}