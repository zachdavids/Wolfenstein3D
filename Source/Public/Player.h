#pragma once

#include "Actor.h"
#include "AABB.h"

#include <GLM/vec3.hpp>
#include <GLM/detail/type_vec2.hpp>
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
		unsigned int TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Horizontal offset to advance to next glyph
	};

	Player(glm::vec3 position, glm::vec3 rotation);

	static void Damage(int damage_points);

	void Input();
	void Update();
	void Render();

	static int GetHealth();
	Camera* GetCamera();
	AABB GetAABB();

private:

	bool shot_;
	static const int m_TotalHealth;
	static const float m_MovementSpeed;

	unsigned int VAO_;
	unsigned int VBO_;

	glm::vec3 movement_vector_;

	Mesh* m_Mesh = nullptr;
	Camera* m_Camera = nullptr;
	Shader* m_DefaultShader = nullptr;
	Shader* m_TextShader = nullptr;

	Texture* m_CurrentAnimation = nullptr;

	void InitText();
	void RenderText(std::string const& text, glm::vec2 position);
	std::map<char, Character> characters_;
};