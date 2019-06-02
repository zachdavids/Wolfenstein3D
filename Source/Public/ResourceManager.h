#pragma once

#include "Resource.h"

#include <unordered_map>
#include <memory>

class ResourceManager
{
public:
	enum class Type
	{
		kShader,
		kTexture
	};

	ResourceManager() = default;
	void Create();
	void AddResource(Type type, std::string const& name, std::string const& path);
	void AddResourceFolder(Type type, std::string const& directory);
	static ResourceManager* Get() { return m_Instance; }
	template <typename T>
	T* GetResource(std::string const& name) const { return dynamic_cast<T*>(m_Resources.find(name)->second.get()); }

private:
	static ResourceManager* m_Instance;
	std::unordered_map<std::string, std::unique_ptr<Resource>> m_Resources;
};

