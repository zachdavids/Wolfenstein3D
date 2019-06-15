#pragma once

#include "Resource.h"

class TextureArray : public Resource
{
public:

	TextureArray(std::string const& filename);
	void Create();
	void Bind() const;
	unsigned int m_ID;
private:


	static const int s_TextureSize;
};

