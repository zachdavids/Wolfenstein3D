#pragma once

#include "Transform.h"

class Actor
{
public:

	Transform m_Transform;
	virtual void Update() {};
	virtual void Render() {};
};