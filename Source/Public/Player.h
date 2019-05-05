#ifndef PLAYER_H
#define PLAYER_H

#include "Camera.h"
#include "Level.h"
#include "Game.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Shader.h"
#include "Audio.h"
#include "TextShader.h"
#include <freetype/ft2build.h>
#include FT_FREETYPE_H

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

	Material* material_;
	Mesh mesh_;
	Transform* transform_;
	Shader* shader_;
	Audio* audio_;
	Texture text_texture;
	TextShader* text_shader_;

	std::vector<Texture*> animations_;

	void AddIndices(std::vector<unsigned int>& indices, int start, bool direction);
	void AddVertices(std::vector<Vertex>& vertices, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords);
	std::vector<float> CalculateTextureCoords(int texture_number);
	void InitText();
	void RenderText(std::string const& text, glm::vec2 position);
	std::map<GLchar, Character> characters_;
};

#endif;