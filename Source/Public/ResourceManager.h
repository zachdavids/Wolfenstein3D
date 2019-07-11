#pragma once

#include "Resource.h"

#include <unordered_map>
#include <tuple>
#include <vector>
#include <memory>

class ResourceManager
{
public:

	ResourceManager() = default;
	void Create();
	void Load();
	template <typename T>
	void AddResource(std::string const& name, std::string const& filename);
	template <typename T>
	void AddResourceFolder(std::string const& folder);
	template <typename T>
	T* GetResource(std::string const& name) const;
	void RemoveResource(std::string const& name);
	static ResourceManager* Get() { return m_Instance; }

private:

	static ResourceManager* m_Instance;
	std::unordered_map<std::string, std::tuple<std::unique_ptr<Resource>, int>> m_ResourceList;
	std::vector<std::string> m_LoadList;
	std::vector<Resource*> m_UnloadList;
	void LoadResources();
	void UnloadResources();
};

template <typename T>
void ResourceManager::AddResource(std::string const& name, std::string const& filename)
{
	auto it = m_ResourceList.find(name);
	if (it != m_ResourceList.end())
	{
		++std::get<1>(it->second);
	}
	else
	{
		m_ResourceList.try_emplace(name, make_tuple(std::make_unique<T>(filename), 0));
		m_LoadList.emplace_back(name);
	}
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
	return (T*)std::get<0>(m_ResourceList.find(name)->second).get();
}

