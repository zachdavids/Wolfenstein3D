#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm.hpp>

#include "BaseLight.h"
#include "Attenuation.h"

class PointLight
{
public:

	PointLight() {};
	PointLight(BaseLight* base_light, Attenuation* attenuation, glm::vec3 position);

	glm::vec3 GetPosition() { return position_; };
	void SetPosition(glm::vec3 position) { position_ = position; };

	BaseLight* GetBaseLight() { return base_light_; };
	void SetBaseLight(BaseLight* base_light) { base_light_ = base_light; };

	Attenuation* GetAttenuation() { return attenuation_; };
	void SetAttenuation(Attenuation* attenuation) { attenuation_ = attenuation; };

private:

	glm::vec3 position_;
	float* position_x_;
	float* position_y_;
	float* position_z_;
	BaseLight* base_light_;
	Attenuation* attenuation_;
};
#endif;