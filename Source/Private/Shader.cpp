#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include <fstream>
#include <sstream>

Shader::Shader(std::string const& path) : 
	Resource(path)
{
}

void Shader::Create()
{
	for (const auto& file : std::filesystem::directory_iterator(m_Path))
	{
		LoadShader(file.path().string());
	}

	Compile();
}

void Shader::Bind() const
{
	glUseProgram(m_ID);
}

void Shader::SetInt(std::string const& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetFloat(std::string const& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetVec3(std::string const& name, glm::vec3 const& value) const
{
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetMat4(std::string const& name, glm::mat4 const& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::LoadShader(std::string const& path)
{
	std::string code;
	ReadFile(&code, path);
	const char* stage_code = code.c_str();

	GLuint stage_id;
	if (path.find("Vertex") != std::string::npos)
	{
		stage_id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (path.find("Fragment") != std::string::npos)
	{
		stage_id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (path.find("TessEval") != std::string::npos)
	{
		stage_id = glCreateShader(GL_TESS_EVALUATION_SHADER);
	}
	else if (path.find("TessControl") != std::string::npos)
	{
		stage_id = glCreateShader(GL_TESS_CONTROL_SHADER);
	}

	glShaderSource(stage_id, 1, &stage_code, NULL);
	glCompileShader(stage_id);

	m_ShaderStages.push_back(stage_id);
}

void Shader::Compile()
{
	GLuint program_id = glCreateProgram();
	for (GLuint stage : m_ShaderStages)
	{
		glAttachShader(program_id, stage);
	}
	glLinkProgram(program_id);

	m_ID = program_id;
}

void Shader::ReadFile(std::string* output, std::string const& path)
{
	std::ifstream stream;
	std::stringstream sstr;

	stream.open(path);
	sstr << stream.rdbuf();
	stream.close();
	*output = sstr.str();
	sstr.str("");
	sstr.clear();
}