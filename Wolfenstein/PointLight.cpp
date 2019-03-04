#include "PointLight.h"

PointLight::PointLight(BaseLight* base_light, Attenuation* attenuation, glm::vec3 position)
{
	base_light_ = base_light;
	attenuation_ = attenuation;
	position_ = position;
}