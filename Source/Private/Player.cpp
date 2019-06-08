#include "Player.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "GameManager.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"
#include "TimeManager.h"
#include "Mesh.h"
#include "AudioManager.h"
#include "Level.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <freetype/ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <GLM/gtc\matrix_transform.hpp>

const int Player::m_TotalHealth = 100;
const float Player::m_MovementSpeed = 0.035f;
const float Player::m_ShootDistance = 10.0f;

const float SIZE1 = 0.2f;
static int health_;

Player::Player(glm::vec3 position, glm::vec3 rotation)
{
	health_ = m_TotalHealth;
	shot_ = false;
	m_Camera = new Camera(position, rotation);
	movement_vector_ = glm::vec3(0.0f);
	InitText();

	m_Transform.SetPosition(position);
	m_Transform.SetRotation(rotation);
	m_Transform.SetScale(glm::vec3(0.5f));

	m_DefaultShader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	m_TextShader = ResourceManager::Get()->GetResource<Shader>("TextShader");
	m_Mesh = ResourceManager::Get()->GetResource<Mesh>("Billboard");
}

void Player::Damage(int damage_points)
{
	if (health_ > m_TotalHealth) 
	{
		health_ = m_TotalHealth;
	}
	health_ -= damage_points;

	if (health_ <= 0) {
		std::cout << "Game Over! Press escape to exit" << "\n";
		//Game::GameOver();
	}
}

void Player::Input()
{
	if (shot_ = true) {
		m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Shoot_1");
	}

	float sensitivity = 0.5f;
	float movAmt = (float)(10 * TimeManager::GetDelta());
	float rotAmt = (float)(100 * TimeManager::GetDelta());

	double mouse_x;
	double mouse_y;
	glfwGetCursorPos(WindowManager::Get()->GetWindow(), &mouse_x, &mouse_y);

	float window_width = (float)WindowManager::Get()->GetWidth();
	float window_height = (float)WindowManager::Get()->GetHeight();

	if (mouse_x != window_width / 2.0f && mouse_y != window_height / 2.0f) {
		m_Camera->MouseControl(mouse_x - window_width / 2.0f, mouse_y - window_height / 2.0f);
	}

	movement_vector_ = glm::vec3(0.0f);

	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_A)) {
		movement_vector_ = movement_vector_ - m_Camera->m_Transform.GetRight();
		AudioManager::Get()->PlayStep();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_D)) {
		movement_vector_ = movement_vector_ + m_Camera->m_Transform.GetRight();
		AudioManager::Get()->PlayStep();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_W)) {
		movement_vector_ = movement_vector_ + m_Camera->m_Transform.GetForward();
		AudioManager::Get()->PlayStep();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_S)) {
		movement_vector_ = movement_vector_ - m_Camera->m_Transform.GetForward();
		AudioManager::Get()->PlayStep();
	}
	if (glfwGetMouseButton(WindowManager::Get()->GetWindow(), GLFW_MOUSE_BUTTON_LEFT)) {
		m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Shoot_3");
		shot_ = true;
		AudioManager::Get()->PlayPlayerGunshot();
		glm::vec3 line_origin = glm::vec3(m_Camera->m_Transform.GetPosition().x, 0, m_Camera->m_Transform.GetPosition().z);
		glm::vec3 line_direction = glm::normalize(glm::vec3(m_Camera->m_Transform.GetForward().x, 0, m_Camera->m_Transform.GetForward().z));
		glm::vec3 line_end = line_origin + (line_direction * m_ShootDistance);
		GameManager::Get()->GetLevel()->CheckIntersection(line_origin, line_end, true);
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_ESCAPE)) {
		exit(1);
	}

	glfwSetCursorPos(WindowManager::Get()->GetWindow(), window_width / 2.0f, window_height / 2.0f);
}

void Player::Update()
{
	movement_vector_.y = 0;

	if (movement_vector_.length() > 0) {
		glm::normalize(movement_vector_);
	}

	glm::vec3 old_position_ = m_Camera->m_Transform.GetPosition();
	glm::vec3 new_position_ = old_position_ + (movement_vector_ * m_MovementSpeed);
	glm::vec3 collision_vector_ = GameManager::Get()->GetLevel()->CheckCollision(old_position_, new_position_, SIZE1, SIZE1);
	
	movement_vector_ *= collision_vector_;

	m_Camera->MoveCamera(movement_vector_, m_MovementSpeed);

	m_Transform.SetPosition(glm::vec3(m_Camera->m_Transform.GetPosition().x + m_Camera->m_Transform.GetForward().x * 0.30f, 0.22f, m_Camera->m_Transform.GetPosition().z + m_Camera->m_Transform.GetForward().z * 0.29f));
	glm::vec3 camera_direction(m_Camera->m_Transform.GetPosition().x - m_Transform.GetPosition().x, m_Camera->m_Transform.GetPosition().y, m_Camera->m_Transform.GetPosition().z - m_Transform.GetPosition().z);
	float camera_angle = -atanf(camera_direction.z / camera_direction.x) + (90.0f * glm::pi<float>() / 180.0f);

	if (camera_direction.x > 0) {
		camera_angle += glm::pi<float>();
	}
	m_Transform.SetRotation(0, camera_angle, 0);
}

int Player::GetHealth() 
{
	return health_;
}

void Player::Render()
{
	m_DefaultShader->Bind();
	m_DefaultShader->SetMat4("model", m_Transform.GetModelMatrix());
	m_CurrentAnimation->Bind();
	m_Mesh->Draw();
	RenderText("HP: " + std::to_string(GetHealth()), glm::vec2(25.0f, 25.0f));
}

void Player::RenderText(std::string const& text, glm::vec2 position)
{
	m_TextShader->Bind();
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO_);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = characters_[*c];

		GLfloat xpos = position.x + ch.Bearing.x;
		GLfloat ypos = position.y - (ch.Size.y - ch.Bearing.y);

		GLfloat w = ch.Size.x;
		GLfloat h = ch.Size.y;

		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		position.x += (ch.Advance >> 6);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Camera* Player::GetCamera()
{
	return m_Camera;
}

void Player::InitText()
{
	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
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

	FT_Set_Pixel_Sizes(face, 0, 48);
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
