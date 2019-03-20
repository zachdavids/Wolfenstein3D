#pragma once

#include <glm.hpp>

class BaseLight;

class DirectionalLight
{
public:

	DirectionalLight(BaseLight* base_light, glm::vec3 direction);

	BaseLight* GetBaseLight() const { return base_light_; };
	void SetBaseLight(BaseLight* base_light) { base_light_ = base_light; };

	glm::vec3 GetDirection() const { return direction_; };
	void SetDirection(glm::vec3 direction) { direction_ = direction; };

private:

	//todo remove raw pointer
	BaseLight* base_light_;
	glm::vec3 direction_;
};