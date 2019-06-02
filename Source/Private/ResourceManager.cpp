#include "ResourceManager.h"
#include "Shader.h"
#include "Texture.h"

#include <iostream>
#include <filesystem>

ResourceManager* ResourceManager::m_Instance;

void ResourceManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kShader,
		"DefaultShader",
		"Default/"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"TileTexture",
		"Tiles/TileTextures.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Medkit",
		"Medkit/Medkit.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Idle",
		"Enemy/Guard/Guard_Idle.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Walk1",
		"Enemy/Guard/Guard_Walk1.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Walk2",
		"Enemy/Guard/Guard_Walk2.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Walk3",
		"Enemy/Guard/Guard_Walk3.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Walk4",
		"Enemy/Guard/Guard_Walk4.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Die1",
		"Enemy/Guard/Guard_Die1.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Die2",
		"Enemy/Guard/Guard_Die2.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Die3",
		"Enemy/Guard/Guard_Die3.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Die4",
		"Enemy/Guard/Guard_Die4.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Pain1",
		"Enemy/Guard/Guard_Pain1.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Pain2",
		"Enemy/Guard/Guard_Pain2.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Shoot1",
		"Enemy/Guard/Guard_Shoot1.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Shoot2",
		"Enemy/Guard/Guard_Shoot2.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Guard_Shoot3",
		"Enemy/Guard/Guard_Shoot3.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Shoot_1",
		"HUD/Shoot_1.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Shoot_2",
		"HUD/Shoot_2.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Shoot_3",
		"HUD/Shoot_3.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Shoot_4",
		"HUD/Shoot_4.png"
	);

	ResourceManager::Get()->AddResource(
		ResourceManager::Type::kTexture,
		"Shoot_5",
		"HUD/Shoot_5.png"
	);
}

void ResourceManager::AddResource(Type type, std::string const& name, std::string const& path)
{
	switch (type)
	{
	case Type::kShader:
		m_Resources.try_emplace(name, std::make_unique<Shader>(path));
		break;
	case Type::kTexture:
		m_Resources.try_emplace(name, std::make_unique<Texture>(path));
		break;
	}
	m_Resources.find(name)->second->Create();
}

void ResourceManager::AddResourceFolder(Type type, std::string const& directory)
{
	for (const auto& file : std::filesystem::directory_iterator(directory))
	{
		std::cout << file.path().string() << std::endl;
		//AddResource(type, std::string const& name, std::string const& path);
	}
}
