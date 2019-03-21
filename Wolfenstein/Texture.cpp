#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string filename)
{
	LoadTexture(filename);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::LoadTexture(std::string filename)
{
	int width, height, num_components;
	unsigned char* image_data = stbi_load(filename.c_str(), &width, &height, &num_components, 4);

	if (image_data == NULL)
	{
		std::cerr << "Texture loading failed for texture: " << filename.c_str() << std::endl;
	}

	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);

	// Repeats texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	stbi_image_free(image_data);
}