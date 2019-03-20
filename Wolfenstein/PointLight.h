#pragma once

#include <glm.hpp>

class BaseLight;
class Attenuation;

class PointLight
{
	glm::vec3 position_;
	BaseLight* base_light_;
	Attenuation* attenuation_;
};