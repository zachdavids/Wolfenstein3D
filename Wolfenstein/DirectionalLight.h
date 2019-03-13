#pragma once

#include <glm.hpp>

#include "BaseLight.h"

class DirectionalLight
{
public:

	DirectionalLight() {};
	DirectionalLight(BaseLight* base_light, glm::vec3 direction);

	BaseLight* GetBaseLight() { return base_light_; };
	void SetBaseLight(BaseLight* base_light) { base_light_ = base_light; };

	glm::vec3 GetDirection() { return direction_; };
	void SetDirection(glm::vec3 direction) { direction_ = direction; };

private:

	BaseLight* base_light_;
	glm::vec3 direction_;
};