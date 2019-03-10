#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <map>
#include <iostream>

#include "Material.h"

class Shader
{
public:

	static Shader* GetInstance()
	{
		static Shader instance;
		return &instance;
	}

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

	void UpdateUniforms(glm::mat4& model_projection, Material* material);

private:

	Shader();
	~Shader() {};
	Shader(Shader const& copy) = delete;
	Shader* operator=(Shader const& copy) = delete;

	GLuint vertex_shader_id_;
	GLuint fragment_shader_id_;
	GLuint shader_program_id_;

	std::map<std::string, unsigned int> uniform_map_;
};

#endif;