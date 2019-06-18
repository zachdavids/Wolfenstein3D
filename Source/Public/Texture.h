#pragma once

#include "Resource.h"

class Texture : public Resource
{
public:

	Texture(std::string const& filename);
	void Create();
	void Bind() const;

private:

	unsigned int m_ID;
};