#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>
#include <iostream>


class Texture
{
public:

	Texture() {};
	Texture(int id);
	Texture(std::string filename);

	int GetId() { return id_; };
	void LoadTexture(std::string filename);
	void Bind();

private:

	GLuint id_;
};

#endif;