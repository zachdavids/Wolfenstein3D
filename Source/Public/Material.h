#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "Texture.h"

class Material
{
public:

	Material(Texture* texture);
	Material(Texture* texture, glm::vec3 color);
	Material(Texture* texture, glm::vec3 color, float specular_intensity, float specular_exponent);

	glm::vec3 GetColor() { return color_; };
	void SetColor(glm::vec3 color) { color_ = color; };

	Texture GetTexture() { return *texture_; };
	void SetTexture(Texture* texture) { texture_ = texture; };

	float GetSpecularIntensity() { return specular_intensity_; };
	void SetSpecularIntensity(float specular_intensity) { specular_intensity_ = specular_intensity; };

	float  GetSpecularExponent() { return specular_exponent_; };
	void  SetSpecularExponent(float specular_exponent) { specular_exponent_ = specular_exponent; };

private:

	float specular_intensity_;
	float specular_exponent_;
	glm::vec3 color_;

	Texture* texture_;
};

#endif;