#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <glad/glad.h>

const std::string Texture::m_Directory = "Resources/Textures/";

Texture::Texture(std::string const& filename) : Resource(m_Directory + filename)
{
}

void Texture::Create()
{
	stbi_set_flip_vertically_on_load(true);
	glGenTextures(1, &m_ID);
	int width;
	int height;
	int num_components;

	unsigned char *data = stbi_load(m_Path.c_str(), &width, &height, &num_components, 4);

	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}