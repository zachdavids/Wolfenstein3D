#include "Wall.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "TextureArray.h"
#include "Mesh.h"

Wall::Wall(glm::vec3 const& position, glm::vec3 const& rotation, int t_id, Mesh* mesh) :
	m_Tid(t_id),
	m_Mesh(mesh)
{
	SetPosition(position);
	SetRotation(rotation);

	m_Model = GetModelMatrix();

	m_Shader = ResourceManager::Get()->GetResource<Shader>("TileShader");
	m_Texture = ResourceManager::Get()->GetResource<TextureArray>("SpriteSheet");
}

void Wall::Render()
{
	m_Shader->Bind();
	m_Shader->SetMat4("model", m_Model);
	m_Shader->SetInt("index", m_Tid);
	m_Texture->Bind();
	m_Mesh->Draw();
}