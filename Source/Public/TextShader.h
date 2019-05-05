#pragma once

#include <string>
#include <glm/mat4x4.hpp>
#include <map>

class Material;
class Texture;

class TextShader
{
public:
	TextShader();

	std::string LoadShaderFile(std::string strFile);
	void AddProgram(std::string filename, int type);
	void AddVertexShader(std::string filename);
	void AddFragmentShader(std::string filename);
	void AddPhongShader(std::string filename);
	void CompileShader();
	void Bind();

	void AddUniform(std::string uniform);
	void SetUniform1i(std::string uniform, const int& value);
	void SetUniform1f(std::string uniform, const float& value);
	void SetUniformVec3(std::string uniform, const glm::vec3& value);
	void SetUniformMat4(std::string uniform, const glm::mat4& value);

	void UpdateUniforms(glm::vec3 color);

private:
	unsigned int vertex_shader_id_;
	unsigned int fragment_shader_id_;
	unsigned int shader_program_id_;

	std::map<std::string, unsigned int> uniform_map_;
};