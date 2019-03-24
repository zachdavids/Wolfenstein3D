#include "Attenuation.h"

Attenuation::Attenuation(float constant, float linear, float exponent)
{
	constant_ = constant;
	linear_ = linear;
	exponent_ = exponent;
}