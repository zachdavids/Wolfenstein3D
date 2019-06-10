#pragma once

#include <map>
#include <GLM/detail/type_vec2.hpp>

class Shader;

class HUD
{
public:

	struct Character
	{
		unsigned int TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		long Advance;    // Horizontal offset to advance to next glyph
	};

	HUD();
	void Render();

private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	Shader* m_TextShader = nullptr;
	void InitText();
	void RenderText(std::string const& text, glm::vec2 position);
	std::map<char, Character> characters_;
};

