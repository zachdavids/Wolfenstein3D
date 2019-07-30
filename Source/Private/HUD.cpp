#include "HUD.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Player.h"
#include "Level.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

#include <iostream>
#include <glad/glad.h>
#include <freetype/ft2build.h>
#include FT_FREETYPE_H

#include <GLM/gtc/matrix_transform.hpp>

HUD::HUD()
{
	m_Shader = ResourceManager::Get()->GetResource<Shader>("HUDShader");
	m_TextShader = ResourceManager::Get()->GetResource<Shader>("TextShader");

	Init();
	InitText();
}

void HUD::Init()
{
	Mesh* mesh = ResourceManager::Get()->GetResource<Mesh>("HUD");
	Texture* gui_texture = ResourceManager::Get()->GetResource<Texture>("HUD1");
	Texture* weapon_texture = ResourceManager::Get()->GetResource<Texture>("Pistol");
	Texture* red_flash = ResourceManager::Get()->GetResource<Texture>("RedScreenFlash");

	HUDElement screen_flash = HUDElement{ 0, glm::vec3(0.0f, -0.70, 0.0f), glm::vec3(2.0f, 2.0f, 2.0f), mesh, red_flash };
	HUDElement gui = HUDElement{ 1.0f, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(2.0f, 0.3f, 1.0f), mesh, gui_texture };
	HUDElement weapon = HUDElement{ 1.0f, glm::vec3(0.775f, -0.95f, 1.5f), glm::vec3(0.3f, 0.2f, 0.2f), mesh, weapon_texture };

	m_Elements = {
		gui,
		weapon,
		screen_flash
	};
}

void HUD::InitText()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, "Resources/Fonts/OpenSans.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, 0, 42);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters_.insert(std::pair<GLchar, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void HUD::Render()
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	m_Shader->Bind();
	for (HUDElement& element : m_Elements)
	{
		element.texture->Bind();
		m_Shader->SetMat4("transform", GetModel(element.position, element.scale));
		m_Shader->SetFloat("alpha", element.alpha);
		element.mesh->Draw();
	}

	EndFlash();

	RenderText(std::to_string(GameManager::Get()->GetLevel()->GetLevelNumber()), glm::vec2(35.0f, 17.0f));
	RenderText(std::to_string(GameManager::Get()->GetPlayer()->GetScore()), glm::vec2(150.0f, 17.0f));
	RenderText(std::to_string(GameManager::Get()->GetPlayer()->GetLives()), glm::vec2(275.0f, 17.0f));
	RenderText(std::to_string(GameManager::Get()->GetPlayer()->GetHealth()), glm::vec2(413.0f, 17.0f));
	RenderText(std::to_string(GameManager::Get()->GetPlayer()->GetAmmo()), glm::vec2(550.0f, 17.0f));
	glEnable(GL_DEPTH_TEST);
}

void HUD::UpdateWeapon(int weapon)
{
	switch (weapon)
	{
	case 0:
		m_Elements[1].texture = ResourceManager::Get()->GetResource<Texture>("Knife");
		break;
	case 1:
		m_Elements[1].texture = ResourceManager::Get()->GetResource<Texture>("Pistol");
		break;
	case 2:
		m_Elements[1].texture = ResourceManager::Get()->GetResource<Texture>("MachineGun");
		break;
	case 3:
		m_Elements[1].texture = ResourceManager::Get()->GetResource<Texture>("Minigun");
		break;
	}
}

void HUD::PlayRedFlash()
{ 
	m_Elements[2].texture = ResourceManager::Get()->GetResource<Texture>("RedScreenFlash");
	m_Elements[2].alpha = 0.75;
}

void HUD::PlayYellowFlash()
{
	m_Elements[2].texture = ResourceManager::Get()->GetResource<Texture>("YellowScreenFlash");
	m_Elements[2].alpha = 0.75;
}

void HUD::EndFlash()
{
	m_Elements[2].alpha = 0;
}

void HUD::RenderText(std::string const& text, glm::vec2 position)
{
	glDisable(GL_CULL_FACE);
	m_TextShader->Bind();
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_VAO);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters_[*c];

		float xpos = position.x + ch.Bearing.x;
		float ypos = position.y - (ch.Size.y - ch.Bearing.y);

		int w = ch.Size.x;
		int h = ch.Size.y;

		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		position.x += (ch.Advance >> 6);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::mat4 HUD::GetModel(glm::vec3 const& position, glm::vec3 const& scale)
{
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), position);
	model_matrix = glm::scale(model_matrix, scale);

	return model_matrix;
}
