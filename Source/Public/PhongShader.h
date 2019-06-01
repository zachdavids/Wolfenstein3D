#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include <glew/GL/glew.h>
#include <GLM/glm.hpp>
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <vector>

#include "Transform.h"
#include "Material.h"
#include "BaseLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class PhongShader
{
public:

	PhongShader();

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
	void SetUniformBL(std::string uniform, BaseLight* base_light);
	void SetUniformDL(std::string uniform, DirectionalLight* directional_light);

	glm::vec3 GetAmbientLight() { return ambient_light_; };
	void SetAmbientLight(glm::vec3 ambient_light) { ambient_light_ = ambient_light; };

	DirectionalLight* GetDirectionalLight() { return directional_light_; };
	void SetDirectionalLight(DirectionalLight* directional_light) { directional_light_ = directional_light; };

	void SetPointLights(std::vector<PointLight> lights);

	void UpdateUniforms(glm::mat4& projection, glm::mat4& model_projection, Material* material, glm::vec3 camera_position);

private:
	
	glm::vec3 ambient_light_;
	DirectionalLight* directional_light_;

	GLuint vertex_shader_id_;
	GLuint fragment_shader_id_;
	GLuint shader_program_id_;

	std::vector<PointLight> point_lights_;
	std::map<std::string, unsigned int> uniform_map_;
};

#endif;
