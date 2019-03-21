#include "PhongShader.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Attenuation.h"
#include "BaseLight.h"

static int MAX_POINT_LIGHTS = 4;

PhongShader::PhongShader()
{
	ambient_light_ = glm::vec3(0.1f, 0.1f, 0.1f);
	directional_light_ = new DirectionalLight{ new BaseLight{ glm::vec3(1, 1, 1), 0.0 }, glm::vec3(1, 1, 1) };

	shader_program_id_ = glCreateProgram();
	AddVertexShader("PhongShader.vertex");
	AddFragmentShader("PhongShader.fragment");
	CompileShader();

	AddUniform("perspective");
	AddUniform("transform");
	AddUniform("base_color_");

	// Ambient Lighting Uniforms
	AddUniform("ambient_light_");

	// Directional Lighting Uniforms
	// TODO: RESEARCH UNIFORM BLOCK
	AddUniform("directional_light.direction");
	AddUniform("directional_light.base_light.color");
	AddUniform("directional_light.base_light.intensity");

	// Specular Lighting Uniforms
	AddUniform("specular_intensity");
	AddUniform("specular_exponent");
	AddUniform("camera_position");

	// Point Lighting Uniforms
	for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
		AddUniform("point_lights[" + std::to_string(i) + "].position");
		AddUniform("point_lights[" + std::to_string(i) + "].base_light.color");
		AddUniform("point_lights[" + std::to_string(i) + "].base_light.intensity");
		AddUniform("point_lights[" + std::to_string(i) + "].attenuation.constant");
		AddUniform("point_lights[" + std::to_string(i) + "].attenuation.linear");
		AddUniform("point_lights[" + std::to_string(i) + "].attenuation.exponent");
	}
}

void PhongShader::Bind()
{
	glUseProgram(shader_program_id_);
}

std::string PhongShader::LoadShaderFile(std::string strFile)
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

void PhongShader::AddVertexShader(std::string filename)
{
	AddProgram(filename, GL_VERTEX_SHADER);
}

void PhongShader::AddFragmentShader(std::string filename)
{
	AddProgram(filename, GL_FRAGMENT_SHADER);
}

void PhongShader::AddPhongShader(const std::string filename)
{
	AddProgram(filename, GL_GEOMETRY_SHADER);
}

void PhongShader::AddProgram(std::string filename, int type)
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

void PhongShader::CompileShader()
{
	glLinkProgram(shader_program_id_);
}

void PhongShader::AddUniform(std::string uniform)
{
	int uniform_location = glGetUniformLocation(shader_program_id_, uniform.c_str());

	uniform_map_.insert(std::pair<std::string, unsigned int>(uniform, uniform_location));
}

void PhongShader::SetPointLights(std::vector<PointLight> lights)
{
	point_lights_ = lights;
}

void PhongShader::SetUniform1i(std::string uniform, const int& value)
{
	glUniform1i(uniform_map_.at(uniform), value);
}

void PhongShader::SetUniform1f(std::string uniform, const float& value)
{
	glUniform1f(uniform_map_.at(uniform), value);
}

void PhongShader::SetUniformVec3(std::string uniform, const glm::vec3& value)
{
	glUniform3f(uniform_map_.at(uniform), value.x, value.y, value.z);
}

void PhongShader::SetUniformMat4(std::string uniform, const glm::mat4& value)
{
	glUniformMatrix4fv(uniform_map_.at(uniform), 1, GL_FALSE, &value[0][0]);
}

void PhongShader::SetUniformBL(std::string uniform, BaseLight* base_light)
{
	SetUniformVec3(uniform + ".color", base_light->color_);
	SetUniform1f(uniform + ".intensity", base_light->intensity_);
}

void PhongShader::SetUniformDL(std::string uniform, DirectionalLight* directional_light)
{
	SetUniformBL(uniform + ".base_light", directional_light->base_light_);
	SetUniformVec3(uniform + ".direction", directional_light->direction_);
}

void PhongShader::UpdateUniforms(glm::mat4& model, glm::mat4& model_projection, Material* material, glm::vec3 camera_position)
{
	// TODO: BIND AND UNBIND TEXTURE
	material->GetTexture().Bind();
	SetUniformMat4("perspective", model_projection);
	SetUniformMat4("transform", model);
	SetUniformVec3("base_color_", material->GetColor());
	SetUniformVec3("ambient_light_", ambient_light_);
	SetUniformDL("directional_light", directional_light_);

	for (unsigned int i = 0; i < point_lights_.size(); i++) {
		SetUniformVec3("point_lights[" + std::to_string(i) + "].position", point_lights_[i].position_);
		SetUniformVec3("point_lights[" + std::to_string(i) + "].base_light.color", point_lights_[i].base_light_->color_);
		SetUniform1f("point_lights[" + std::to_string(i) + "].base_light.intensity", point_lights_[i].base_light_->intensity_);
		SetUniform1f("point_lights[" + std::to_string(i) + "].attenuation.constant", point_lights_[i].attenuation_->constant_);
		SetUniform1f("point_lights[" + std::to_string(i) + "].attenuation.linear", point_lights_[i].attenuation_->linear_);
		SetUniform1f("point_lights[" + std::to_string(i) + "].attenuation.exponent", point_lights_[i].attenuation_->exponent_);
	}

	// Specular Lighting Uniforms
	SetUniform1f("specular_intensity", material->GetSpecularIntensity());
	SetUniform1f("specular_exponent", material->GetSpecularExponent());
	SetUniformVec3("camera_position", camera_position);
}



