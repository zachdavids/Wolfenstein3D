#pragma once

#include "Resource.h"

class TextureArray : public Resource
{
public:

	TextureArray(std::string const& filename);
	void Create();
	void Bind() const;
	static constexpr int s_TextureSize = 64;

private:

	unsigned int m_ID;
};