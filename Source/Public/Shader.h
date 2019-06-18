#pragma once

#include "Resource.h"

#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>

#include <vector>

class Shader : public Resource
{
public:

	Shader(std::string const& path);
	void Create();
	void Bind() const;
	void SetInt(std::string const& name, int value) const;
	void SetFloat(std::string const& name, float value) const;
	void SetVec3(std::string const& name, glm::vec3 const& value) const;
	void SetMat4(std::string const& name, glm::mat4 const& value) const;

private:

	unsigned int m_ID;
	std::vector<unsigned int> m_ShaderStages;
	void LoadShader(std::string const& path);
	void Compile();
	void ReadFile(std::string* output, std::string const& path);
};