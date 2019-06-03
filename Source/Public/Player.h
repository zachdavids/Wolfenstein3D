#pragma once

#include "Camera.h"
#include "Level.h"
#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Transform.h"
#include "AudioManager.h"
#include "TextShader.h"
#include <freetype/ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>

class Texture;

class Player
{
public:

	struct Character 
	{
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

	Player(glm::vec3 position, float yaw, float pitch);

	static void Damage(int damage_points);

	void Input();
	void Update();
	void Render();

	static int GetHealth();

	static Camera* GetCamera();

private:

	bool shot_;

	unsigned int VAO_;
	unsigned int VBO_;

	glm::vec3 old_position_;
	glm::vec3 new_position_;
	glm::vec3 collision_vector_;
	glm::vec3 movement_vector_;

	Mesh* m_Mesh = nullptr;
	Transform* transform_;
	Audio* audio_;
	TextShader* text_shader_;

	Texture* m_CurrentAnimation = nullptr;

	void InitText();
	void RenderText(std::string const& text, glm::vec2 position);
	std::map<GLchar, Character> characters_;
};