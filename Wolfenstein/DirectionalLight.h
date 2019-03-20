#pragma once

#include <glm.hpp>

class BaseLight;

struct DirectionalLight
{
	//todo remove raw pointer
	BaseLight* base_light_;
	glm::vec3 direction_;
};