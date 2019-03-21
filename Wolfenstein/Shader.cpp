#include "Shader.h"

#include <cassert>

Shader::Shader()
{
	shader_program_id_ = glCreateProgram();
	AddVertexShader("Shader.vertex");
	AddFragmentShader("Shader.fragment");
	CompileShader();

	AddUniform("transform");
	AddUniform("color");
}

void Shader::Bind()
{
	glUseProgram(shader_program_id_);
}

std::string Shader::LoadShaderFile(std::string strFile)
{
	std::ifstream fin(strFile.c_str());

	if (!fin)
		return "";

	std::string strLine = "";
	std::string strText = "";

	while (getline(fin, strLine))
	{
		strText = strText + "\n" + strLine;
	}

	fin.close();

	return strText;
}

void Shader::AddVertexShader(std::string filename)
{
	AddProgram(filename, GL_VERTEX_SHADER);
}

void Shader::AddFragmentShader(std::string filename)
{
	AddProgram(filename, GL_FRAGMENT_SHADER);
}

void Shader::AddPhongShader(const std::string filename)
{
	AddProgram(filename, GL_GEOMETRY_SHADER);
}

void Shader::AddProgram(std::string filename, int type)
{
	std::string shader;

	shader = LoadShaderFile(filename.c_str());
	const char *shader_file = shader.c_str();

	int shader_id = glCreateShader(type);

	glShaderSource(shader_id, 1, &shader_file, nullptr);
	glCompileShader(shader_id);

	GLint success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar info_log[1024];

		glGetShaderInfoLog(shader_id, 1024, NULL, info_log);
		std::cerr << "Error compiling shader" << *info_log;
		
	}

	glAttachShader(shader_program_id_, shader_id);
}

void Shader::CompileShader()
{
	glLinkProgram(shader_program_id_);
}

void Shader::AddUniform(std::string uniform)
{
	int uniform_location = glGetUniformLocation(shader_program_id_, uniform.c_str());

	uniform_map_.insert(std::pair<std::string, unsigned int>(uniform, uniform_location));
}

void Shader::SetUniform1i(std::string uniform, const int& value)
{
	glUniform1i(uniform_map_.at(uniform), value);
}

void Shader::SetUniform1f(std::string uniform, const float& value)
{
	glUniform1f(uniform_map_.at(uniform), value);
}

void Shader::SetUniformVec3(std::string uniform, const glm::vec3& value)
{
	glUniform3f(uniform_map_.at(uniform), value.x, value.y, value.z);
}

void Shader::SetUniformMat4(std::string uniform, const glm::mat4& value)
{
	glUniformMatrix4fv(uniform_map_.at(uniform), 1, GL_FALSE, &value[0][0]);
}

void Shader::UpdateUniforms(glm::mat4& model_projection, Material* material)
{
	// TODO: BIND AND UNBIND TEXTURE
	material->GetTexture().Bind();
	SetUniformMat4("transform", model_projection);
	SetUniformVec3("color", material->GetColor());
}



