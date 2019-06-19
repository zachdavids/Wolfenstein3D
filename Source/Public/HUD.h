#pragma once

#include "HUDElement.h"

#include <GLM/detail/type_vec2.hpp>
#include <GLM/glm.hpp>

#include <map>
#include <vector>

class Shader;
class Mesh;
class Texture;

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
	void Init();
	void Render();
	void UpdateWeapon(int weapon);
	void PlayRedFlash();
	void PlayYellowFlash();
	void EndFlash();

private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	std::vector<HUDElement> m_Elements;
	Shader* m_Shader = nullptr;
	Shader* m_TextShader = nullptr;
	void InitText();
	void RenderText(std::string const& text, glm::vec2& position);
	std::map<char, Character> characters_;
	glm::mat4 GetModel(glm::vec3 const& position, glm::vec3 const& scale);
};

