#pragma once

class Attenuation
{
public:

	Attenuation() {};
	Attenuation(float constant, float linear, float exponent);

	float GetConstant() { return constant_; };
	void SetConstant(float constant) { constant_ = constant; };

	float GetLinear() { return linear_; };
	void SetLinear(float linear) { linear_ = linear; };

	float GetExponent() { return exponent_; };
	void SetExponent(float exponent) { exponent_ = exponent; };

private:

	float constant_;
	float linear_;
	float exponent_;
};