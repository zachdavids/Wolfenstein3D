#ifndef BASELIGHT_H
#define BASELIGHT_H

#include <GLM/glm.hpp>

class BaseLight
{
public:

	BaseLight() {};
	BaseLight(glm::vec3 color, float intensity);

	glm::vec3 GetColor() { return color_; };
	void SetColor(glm::vec3 color) { color_ = color; };

	float GetIntensity() { return intensity_; };
	void SetIntensity(float intensity) { intensity_ = intensity; };

private:

	glm::vec3 color_;
	float intensity_;
};

#endif;