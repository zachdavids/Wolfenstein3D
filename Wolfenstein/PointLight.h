#pragma once

#include <glm.hpp>

struct BaseLight;
struct Attenuation;

struct PointLight
{
	glm::vec3 position_;
	BaseLight* base_light_;
	Attenuation* attenuation_;
};