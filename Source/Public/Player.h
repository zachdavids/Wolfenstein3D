#pragma once

#include "Actor.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>

class Texture;
class Mesh;
class Camera;
class TextShader;
class Shader;

class Player : public Actor
{
public:

	struct Character 
	{
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

	Player(glm::vec3 position, glm::vec3 rotation);

	static void Damage(int damage_points);

	void Input();
	void Update();
	void Render();

	static int GetHealth();

	Camera* GetCamera();

private:

	bool shot_;

	unsigned int VAO_;
	unsigned int VBO_;

	glm::vec3 old_position_;
	glm::vec3 new_position_;
	glm::vec3 collision_vector_;
	glm::vec3 movement_vector_;

	Mesh* m_Mesh = nullptr;
	Shader* m_DefaultShader = nullptr;
	Shader* m_TextShader = nullptr;

	Texture* m_CurrentAnimation = nullptr;

	void InitText();
	void RenderText(std::string const& text, glm::vec2 position);
	std::map<GLchar, Character> characters_;
};