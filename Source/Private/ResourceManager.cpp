#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

#include <iostream>
#include <filesystem>

ResourceManager* ResourceManager::m_Instance;

const std::string ResourceManager::m_TextureDir = "Resources/Textures/";
const std::string ResourceManager::m_ShaderDir = "Resources/Shaders/";
const std::string ResourceManager::m_MeshDir = "Resources/Meshes/";

void ResourceManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kShader,
		"DefaultShader",
		"Default/"
	);

		ResourceManager::Get()->AddResourceFolder(
		ResourceManager::Type::kMesh,
		""
	);

	ResourceManager::Get()->AddResourceFolder(
		ResourceManager::Type::kTexture,
		"Enemy/Guard/"
	);

	ResourceManager::Get()->AddResourceFolder(
		ResourceManager::Type::kTexture,
		"HUD/"
	);

	ResourceManager::Get()->AddResourceFolder(
		ResourceManager::Type::kTexture,
		"Medkit/"
	);

	ResourceManager::Get()->AddResourceFolder(
		ResourceManager::Type::kTexture,
		"Tiles/"
	);
}

void ResourceManager::AddResource(Type type, std::string const& name, std::string const& filename)
{
	switch (type)
	{
	case Type::kShader:
		m_Resources.try_emplace(name, std::make_unique<Shader>(m_ShaderDir + filename));
		break;
	case Type::kTexture:
		m_Resources.try_emplace(name, std::make_unique<Texture>(m_TextureDir + filename));
		break;
	case Type::kMesh:
		m_Resources.try_emplace(name, std::make_unique<Mesh>(m_MeshDir + filename));
		break;
	}
	m_Resources.find(name)->second->Create();
}

void ResourceManager::AddResourceFolder(Type type, std::string const& folder)
{
	std::string directory;
	switch (type)
	{
	case Type::kShader:
		directory = m_ShaderDir + folder;
		break;
	case Type::kTexture:
		directory = m_TextureDir + folder;
		break;
	case Type::kMesh:
		directory = m_MeshDir + folder;
		break;
	}

	for (const auto& file : std::filesystem::directory_iterator(directory))
	{
		AddResource(
			type, 
			file.path().stem().string(),
			folder + file.path().filename().string()
		);
	}
}
