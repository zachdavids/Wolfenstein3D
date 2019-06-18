#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "TextureArray.h"

#include <filesystem>

ResourceManager* ResourceManager::m_Instance;

void ResourceManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	ResourceManager::Get()->AddResource<Shader>(
		"DefaultShader",
		"Resources/Shaders/Default/"
	);

	ResourceManager::Get()->AddResource<Shader>(
		"TileShader",
		"Resources/Shaders/Tilesheet/"
	);

	ResourceManager::Get()->AddResource<Shader>(
		"TextShader",
		"Resources/Shaders/Text/"
	);

	ResourceManager::Get()->AddResource<Shader>(
		"HUDShader",
		"Resources/Shaders/HUD/"
		);

		ResourceManager::Get()->AddResourceFolder<Mesh>(
		"Resources/Meshes/"
	);

	ResourceManager::Get()->AddResourceFolder<Texture>(
		"Resources/Textures/Enemy/Guard/"
	);

	ResourceManager::Get()->AddResourceFolder<Texture>(
		"Resources/Textures/HUD/"
	);

	ResourceManager::Get()->AddResourceFolder<TextureArray>(
		"Resources/Tilesheets/"
	);
}