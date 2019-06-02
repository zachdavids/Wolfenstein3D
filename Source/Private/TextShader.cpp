#include "TextShader.h"
#include "Material.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <iostream>

TextShader::TextShader()
{
	shader_program_id_ = glCreateProgram();
	AddVertexShader("Resources/Shaders/TextShader.vertex");
	AddFragmentShader("Resources/Shaders/TextShader.fragment");
	CompileShader();

	AddUniform("projection");
	AddUniform("color");
}

void TextShader::Bind()
{
	glUseProgram(shader_program_id_);
}

std::string TextShader::LoadShaderFile(std::string strFile)
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

void TextShader::AddVertexShader(std::string filename)
{
	AddProgram(filename, GL_VERTEX_SHADER);
}

void TextShader::AddFragmentShader(std::string filename)
{
	AddProgram(filename, GL_FRAGMENT_SHADER);
}

void TextShader::AddPhongShader(const std::string filename)
{
	AddProgram(filename, GL_GEOMETRY_SHADER);
}

void TextShader::AddProgram(std::string filename, int type)
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
		GLchar InfoLog[1024];

		glGetShaderInfoLog(shader_id, 1024, NULL, InfoLog);
		std::cout << "Error compiling shader type" << shader << InfoLog << std::endl;

	}

	glAttachShader(shader_program_id_, shader_id);
}

void TextShader::CompileShader()
{
	glLinkProgram(shader_program_id_);
}

void TextShader::AddUniform(std::string uniform)
{
	int uniform_location = glGetUniformLocation(shader_program_id_, uniform.c_str());

	uniform_map_.insert(std::pair<std::string, unsigned int>(uniform, uniform_location));
}

void TextShader::SetUniform1i(std::string uniform, const int& value)
{
	glUniform1i(uniform_map_.at(uniform), value);
}

void TextShader::SetUniform1f(std::string uniform, const float& value)
{
	glUniform1f(uniform_map_.at(uniform), value);
}

void TextShader::SetUniformVec3(std::string uniform, const glm::vec3& value)
{
	glUniform3f(uniform_map_.at(uniform), value.x, value.y, value.z);
}

void TextShader::SetUniformMat4(std::string uniform, const glm::mat4& value)
{
	glUniformMatrix4fv(uniform_map_.at(uniform), 1, GL_FALSE, &value[0][0]);
}

void TextShader::UpdateUniforms(glm::vec3 color)
{
	SetUniformMat4("projection", glm::ortho(0.0f, 800.0f, 0.0f, 600.0f));
	SetUniformVec3("color", color);
}



