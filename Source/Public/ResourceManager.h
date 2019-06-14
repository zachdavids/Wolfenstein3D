#pragma once

#include "Resource.h"

#include <unordered_map>
#include <memory>

class ResourceManager
{
public:

	ResourceManager() = default;
	void Create();
	template <typename T>
	void AddResource(std::string const& name, std::string const& filename);
	template <typename T>
	void AddResourceFolder(std::string const& folder);
	static ResourceManager* Get() { return m_Instance; }
	template <typename T>
	T* GetResource(std::string const& name) const;

private:

	static ResourceManager* m_Instance;
	std::unordered_map<std::string, std::unique_ptr<Resource>> m_Resources;
};

template <typename T>
void ResourceManager::AddResource(std::string const& name, std::string const& filename)
{
	std::unique_ptr<T> resource = std::make_unique<T>(filename);
	resource->Create();
	m_Resources.try_emplace(name, std::move(resource));
}

template <typename T>
void ResourceManager::AddResourceFolder(std::string const& folder)
{
	for (const auto& file : std::filesystem::directory_iterator(folder))
	{
		AddResource<T>(
			file.path().stem().string(),
			folder + file.path().filename().string()
		);
	}
}

template <typename T>
T* ResourceManager::GetResource(std::string const& name) const
{
	return (T*)m_Resources.find(name)->second.get();
}

