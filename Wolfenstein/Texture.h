#pragma once

#include <glew.h>
#include <string>
#include <iostream>

class Texture
{
public:

	Texture(std::string filename);

	int GetId() const { return id_; };
	void LoadTexture(std::string filename);
	void Bind();

private:

	GLuint id_;
};