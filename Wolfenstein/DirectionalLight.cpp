#include "DirectionalLight.h"
#include "BaseLight.h"

DirectionalLight::DirectionalLight(BaseLight* base_light, glm::vec3 direction) :
	base_light_(base_light), direction_(direction)
{
}