#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "TextureArray.h"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>

#include <iostream>

ResourceManager* ResourceManager::m_Instance;

using json = nlohmann::json;

/*
TODO	Remove Load from Create() and separate global resources from level resources
		so that individual level resources can be loaded in at point of level creation.
		Also implement the public Unload() function for when levels are exited.
*/

void ResourceManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	LoadGlobalResources();
}

void ResourceManager::LoadLevelResources(nlohmann::json& data)
{
	for (std::string const& path : data["meshes"])
	{
		ResourceManager::Get()->AddResource<Mesh>(path, path);
	}

	for (std::string const& path : data["shaders"])
	{
		ResourceManager::Get()->AddResource<Shader>(path, path);
	}

	for (std::string const& path : data["textures"])
	{
		ResourceManager::Get()->AddResource<Texture>(path, path);
	}

	for (std::string const& path : data["texturearrays"])
	{
		ResourceManager::Get()->AddResource<TextureArray>(path, path);
	}

	LoadResources();
}

void ResourceManager::LoadGlobalResources()
{
	std::ifstream file(s_ConfigFilePath);
	json data;
	file >> data;
	file.close();

	std::cout << "Global Resources" << std::endl;
	for (std::string const& path : data["meshes"])
	{
		std::cout << path << std::endl;
		ResourceManager::Get()->AddResource<Mesh>(path,	path);
	}

	for (std::string const& path : data["shaders"])
	{
		std::cout << path << std::endl;
		ResourceManager::Get()->AddResource<Shader>(path, path);
	}

	for (std::string const& path : data["textures"])
	{
		std::cout << path << std::endl;
		ResourceManager::Get()->AddResource<Texture>(path, path);
	}

	for (std::string const& path : data["texturearrays"])
	{
		std::cout << path << std::endl;
		ResourceManager::Get()->AddResource<TextureArray>(path, path);
	}

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
