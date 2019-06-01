#pragma once

#include "Resource.h"

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <string>
#include <vector>

class Shader : public Resource
{
public:
	Shader(std::string const& path);
	void Create();
	void Use() const;
	void SetInt(std::string const& name, int value) const;
	void SetFloat(std::string const& name, float value) const;
	void SetVec3(std::string const& name, glm::vec3 const& value) const;
	void SetMat4(std::string const& name, glm::mat4 const& value) const;
private:
	GLuint m_ID;
	static const std::string m_Directory;

	std::vector<GLuint> m_ShaderStages;
	void LoadShader(std::string const& path);
	void Compile();
	void ReadFile(std::string* output, std::string const& path);
};