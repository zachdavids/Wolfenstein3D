#include "Material.h"

Material::Material(Texture* texture)
{
	texture_ = texture;
	color_ = glm::vec3(1.0f, 1.0f, 1.0f);
	specular_intensity_ = 2;
	specular_exponent_ = 32;
}

Material::Material(Texture* texture, glm::vec3 color)
{
	texture_ = texture;
	color_ = color;
	specular_intensity_ = 2;
	specular_exponent_ = 32;
}

Material::Material(Texture* texture, glm::vec3 color, float specular_intensity, float specular_exponent)
{
	texture_ = texture;
	color_ = color;
	specular_intensity_ = specular_intensity;
	specular_exponent_ = specular_exponent;
}