#include "ResourceManager.h"
#include "Shader.h"

#include <iostream>

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
}

void ResourceManager::AddResource(Type type, std::string const& name, std::string const& path)
{
	switch (type)
	{
	case Type::kShader:
		m_Resources.try_emplace(name, std::make_unique<Shader>(path));
		break;
	}
	m_Resources.find(name)->second->Create();
}