#pragma once

#include <glm.hpp>

struct BaseLight;

struct DirectionalLight
{
	//todo remove raw pointer
	BaseLight* base_light_;
	glm::vec3 direction_;
};