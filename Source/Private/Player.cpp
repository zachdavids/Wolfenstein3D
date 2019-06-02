#include "Player.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "Texture.h"
#include "Shader.h"

#include <GLFW/glfw3.h>

const float SCALE = 0.5f;
const float LENGTH = 1.0f;
const float HEIGHT = 1.0f;
const int NUM_TEXTURES_X = 1;
const int NUM_TEXTURES_Y = 1;

const int HP = 100;
const float SIZE1 = 0.2f;
const float MOVEMENT_SPEED = 0.035f;
const float SHOOT_DISTANCE = 10.0f;

static int health_;
static Camera* camera_;

Player::Player(glm::vec3 position, float yaw, float pitch)
{
	health_ = HP;
	shot_ = false;
	audio_ = new Audio();
	camera_ = new Camera(position, yaw, pitch);
	movement_vector_ = glm::vec3(0.0f);
	text_shader_ = new TextShader();
	InitText();

	transform_ = new Transform();
	transform_->SetTranslation(glm::vec3(camera_->GetPosition().x, 0, camera_->GetPosition().z));
	transform_->SetScale(glm::vec3(SCALE, SCALE, SCALE));
	transform_->SetCamera(camera_);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	AddIndices(indices, vertices.size(), false);
	AddVertices(vertices, false, 0, 0, 0, CalculateTextureCoords(27));

	mesh_.InitializeMesh(vertices, indices);
}

void Player::Damage(int damage_points)
{
	if (health_ > HP) {
		health_ = HP;
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
		camera_->MouseControl(mouse_x - window_width / 2.0f, mouse_y - window_height / 2.0f);
	}

	movement_vector_ = glm::vec3(0.0f);

	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_A)) {
		movement_vector_ = movement_vector_ - camera_->GetRight();
		audio_->PlayStep();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_D)) {
		movement_vector_ = movement_vector_ + camera_->GetRight();
		audio_->PlayStep();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_W)) {
		movement_vector_ = movement_vector_ + camera_->GetForward();
		audio_->PlayStep();
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_S)) {
		movement_vector_ = movement_vector_ - camera_->GetForward();
		audio_->PlayStep();
	}
	if (glfwGetMouseButton(WindowManager::Get()->GetWindow(), GLFW_MOUSE_BUTTON_LEFT)) {
		m_CurrentAnimation = ResourceManager::Get()->GetResource<Texture>("Shoot_3");
		shot_ = true;
		audio_->PlayPlayerGunshot();
		glm::vec3 line_origin = glm::vec3(camera_->GetPosition().x, 0, camera_->GetPosition().z);
		glm::vec3 line_direction = glm::normalize(glm::vec3(camera_->GetForward().x, 0, camera_->GetForward().z));
		glm::vec3 line_end = line_origin + (line_direction * SHOOT_DISTANCE);
		Level::CheckIntersection(line_origin, line_end, true);
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

	old_position_ = camera_->GetPosition();
	new_position_ = old_position_ + (movement_vector_ * MOVEMENT_SPEED);
	collision_vector_ = Level::CheckCollision(old_position_, new_position_, SIZE1, SIZE1);
	
	movement_vector_ *= collision_vector_;

	camera_->MoveCamera(movement_vector_, MOVEMENT_SPEED);

	transform_->SetTranslation(glm::vec3(camera_->GetPosition().x + camera_->GetForward().x * 0.30f, 0.22f, camera_->GetPosition().z + camera_->GetForward().z * 0.29f));
	glm::vec3 camera_direction(transform_->GetCamera()->GetPosition().x - transform_->GetTranslation().x, transform_->GetCamera()->GetPosition().y, transform_->GetCamera()->GetPosition().z - transform_->GetTranslation().z);
	float camera_angle = -atanf(camera_direction.z / camera_direction.x) + (90.0f * glm::pi<float>() / 180.0f);

	if (camera_direction.x > 0) {
		camera_angle += glm::pi<float>();
	}
	else {
	}
	transform_->SetRotation(0, camera_angle, 0);
}

int Player::GetHealth() {
	return health_;
}

void Player::Render()
{
	Shader* shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");
	shader->Bind();
	shader->SetMat4("transform", transform_->GetModelProjection());
	m_CurrentAnimation->Bind();
	mesh_.Draw();
	RenderText("HP: " + std::to_string(GetHealth()), glm::vec2(25.0f, 25.0f));
}

void Player::RenderText(std::string const& text, glm::vec2 position)
{
	text_shader_->Bind();
	text_shader_->UpdateUniforms(glm::vec3(0.5, 0.8f, 0.2f));
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
	return camera_;
}

void Player::AddIndices(std::vector<unsigned int>& indices, int start, bool direction)
{
	indices.push_back(start + 0);
	indices.push_back(start + 1);
	indices.push_back(start + 2);

	indices.push_back(start + 0);
	indices.push_back(start + 2);
	indices.push_back(start + 3);

}

void Player::AddVertices(std::vector<Vertex>& vertices, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords)
{
	vertices.push_back(Vertex{ glm::vec3(-LENGTH / 2, y_coord, z_coord), glm::vec2(texture_coords[0], texture_coords[2]) });
	vertices.push_back(Vertex{ glm::vec3(-LENGTH / 2, HEIGHT, z_coord), glm::vec2(texture_coords[0], texture_coords[3]) });
	vertices.push_back(Vertex{ glm::vec3(LENGTH / 2, HEIGHT, z_coord), glm::vec2(texture_coords[1], texture_coords[3]) });
	vertices.push_back(Vertex{ glm::vec3(LENGTH / 2, y_coord, z_coord), glm::vec2(texture_coords[1], texture_coords[2]) });
}

std::vector<float> Player::CalculateTextureCoords(int texture_number)
{
	float texture_x = (float)(texture_number % NUM_TEXTURES_X);
	float texture_y = (float)(texture_number / NUM_TEXTURES_X);
	std::vector<float> texture_coords;

	texture_coords.push_back((1.0f / NUM_TEXTURES_X) + (1.0f / NUM_TEXTURES_X) * texture_x);
	texture_coords.push_back((texture_coords[0] - (1.0f / NUM_TEXTURES_X)));
	texture_coords.push_back((1.0f / NUM_TEXTURES_Y) + (1.0f / NUM_TEXTURES_Y) * texture_y);
	texture_coords.push_back((texture_coords[2] - (1.0f / NUM_TEXTURES_Y)));

	return texture_coords;
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
