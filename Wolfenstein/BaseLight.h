#pragma once

#include <glm.hpp>

class BaseLight
{
public:

	BaseLight(glm::vec3 color, float intensity);

	glm::vec3 GetColor() const { return color_; };
	void SetColor(glm::vec3 color) { color_ = color; };

	float GetIntensity() const { return intensity_; };
	void SetIntensity(float intensity) { intensity_ = intensity; };

private:

	glm::vec3 color_;
	float intensity_;
};