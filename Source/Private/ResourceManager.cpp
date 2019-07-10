#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "TextureArray.h"

#include <filesystem>

ResourceManager* ResourceManager::m_Instance;

/*
TODO	Remove Load from Create() and separate global resources from level resources
		so that individual level resources can be loaded in at point of level creation.
		Also implement the public Unload() function for when levels are exited.
*/

void ResourceManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	Load();
}

void ResourceManager::Load()
{
	//Temporary
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
		"Resources/Textures/HUD/"
		);

	ResourceManager::Get()->AddResourceFolder<TextureArray>(
		"Resources/Tilesheets/"
		);
	// Temporary Ends

	LoadResources();
}

void ResourceManager::RemoveResource(std::string const& name)
{
	auto it = m_ResourceList.find(name);
	if (it != m_ResourceList.end())
	{
		++std::get<1>(it->second);
		if (std::get<1>(it->second) == 0)
		{
			m_UnloadList.emplace_back(std::get<0>(m_ResourceList.find(name)->second).release());
		}
	}
}

void ResourceManager::LoadResources()
{
	for (std::string const& name : m_LoadList)
	{
		std::get<0>(m_ResourceList.find(name)->second)->Create();
	}

	m_LoadList.clear();
}

void ResourceManager::UnloadResources()
{
	for (Resource* resource : m_UnloadList)
	{
		delete resource;
	}

	m_UnloadList.clear();
}
