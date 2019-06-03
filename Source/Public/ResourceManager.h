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
		kTexture,
		kMesh
	};

	ResourceManager() = default;
	void Create();
	void AddResource(Type type, std::string const& name, std::string const& filename);
	void AddResourceFolder(Type type, std::string const& folder);
	static ResourceManager* Get() { return m_Instance; }
	template <typename T>
	T* GetResource(std::string const& name) const { return (T*)m_Resources.find(name)->second.get(); }

private:
	static ResourceManager* m_Instance;
	static const std::string m_TextureDir;
	static const std::string m_ShaderDir;
	static const std::string m_MeshDir;
	std::unordered_map<std::string, std::unique_ptr<Resource>> m_Resources;
};

