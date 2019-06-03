#pragma once

#include <string>

class Resource
{
public:

	Resource() = default;
	Resource(std::string const& path);
	virtual void Create() = 0;

protected:

	std::string m_Path;
};


