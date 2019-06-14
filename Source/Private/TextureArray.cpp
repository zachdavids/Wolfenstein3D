#include "TextureArray.h"
#include "stb_image.h"

#include <glad/glad.h>

TextureArray::TextureArray(std::string const& filename) : Resource(filename)
{
}

void TextureArray::Create()
{
	stbi_set_flip_vertically_on_load(true);

	int width;
	int height;
	int num_components;
	unsigned char *data = stbi_load(m_Path.c_str(), &width, &height, &num_components, 4);

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_ID);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA, width, height / 114, 114);
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height / 114, 114, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_LEVEL, 4);

	stbi_image_free(data);
}

void TextureArray::Bind() const
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_ID);
}
