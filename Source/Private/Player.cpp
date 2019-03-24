#include "Player.h"

const float SCALE = 0.5f;
const float LENGTH = 1.0f;
const float HEIGHT = 1.0f;
const int NUM_TEXTURES_X = 1;
const int NUM_TEXTURES_Y = 1;

const float HP = 100.0f;
const float SIZE = 0.2f;
const float MOVEMENT_SPEED = 0.035f;
const float SHOOT_DISTANCE = 10.0f;

static int health_;
static Camera* camera_ = new Camera();


Player::Player(glm::vec3 position, int yaw, int pitch)
{
	health_ = HP;
	shot_ = false;
	audio_ = new Audio();
	camera_ = new Camera(position, yaw, pitch);
	movement_vector_ = glm::vec3(0.0f);

	animations_.push_back(new Texture("Enemy/pngs/s1_1.png"));
	animations_.push_back(new Texture("Enemy/pngs/s2_2.png"));
	animations_.push_back(new Texture("Enemy/pngs/s3_3.png"));
	animations_.push_back(new Texture("Enemy/pngs/s4_4.png"));
	animations_.push_back(new Texture("Enemy/pngs/s5_5.png"));
	
	animations_2.push_back(new Texture("Numbers/0.png"));
	animations_2.push_back(new Texture("Numbers/1.png"));
	animations_2.push_back(new Texture("Numbers/2.png"));
	animations_2.push_back(new Texture("Numbers/3.png"));
	animations_2.push_back(new Texture("Numbers/4.png"));
	animations_2.push_back(new Texture("Numbers/5.png"));
	animations_2.push_back(new Texture("Numbers/6.png"));
	animations_2.push_back(new Texture("Numbers/7.png"));
	animations_2.push_back(new Texture("Numbers/8.png"));
	animations_2.push_back(new Texture("Numbers/9.png"));

	transform_ = new Transform();
	transform_->SetTranslation(glm::vec3(camera_->GetPosition().x, 0, camera_->GetPosition().z));
	transform_->SetScale(glm::vec3(SCALE, SCALE, SCALE));
	transform_->SetCamera(camera_);

	transform_2 = new Transform();
	transform_2->SetTranslation(glm::vec3(camera_->GetPosition().x, 0, camera_->GetPosition().z));
	transform_2->SetScale(glm::vec3(0.05, 0.05, 0.05));
	transform_2->SetCamera(camera_);

	transform_3 = new Transform();
	transform_3->SetTranslation(glm::vec3(camera_->GetPosition().x, 0, camera_->GetPosition().z));
	transform_3->SetScale(glm::vec3(0.05, 0.05, 0.05));
	transform_3->SetCamera(camera_);

	transform_4 = new Transform();
	transform_4->SetTranslation(glm::vec3(camera_->GetPosition().x, 0, camera_->GetPosition().z));
	transform_4->SetScale(glm::vec3(0.05, 0.05, 0.05));
	transform_4->SetCamera(camera_);

	material_ = new Material(animations_[0]);
	material_2 = new Material(animations_2[1]);
	material_3 = new Material(animations_2[0]);
	material_4 = new Material(animations_2[0]);

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
		Game::GameOver();
	}
}

void Player::Input()
{
	if (shot_ = true) {
		material_->SetTexture(animations_[0]);
	}

	float sensitivity = 0.5f;
	float movAmt = (float)(10 * TimeManager::GetDelta());
	float rotAmt = (float)(100 * TimeManager::GetDelta());

	if (Input::GetMousePosition().x != Window::GetWidth() / 2 && Input::GetMousePosition().y != Window::GetHeight() / 2) {
		camera_->MouseControl(Input::GetMousePosition().x - Window::GetWidth() / 2, Input::GetMousePosition().y - Window::GetHeight() / 2);
	}

	movement_vector_ = glm::vec3(0.0f);

	if (Input::GetKey(Input::KEY_A)) {
		movement_vector_ = movement_vector_ - camera_->GetRightDirection();
		audio_->PlayStep();
	}
	if (Input::GetKey(Input::KEY_D)) {
		movement_vector_ = movement_vector_ + camera_->GetRightDirection();
		audio_->PlayStep();
	}
	if (Input::GetKey(Input::KEY_W)) {
		movement_vector_ = movement_vector_ + camera_->GetViewDirection();
		audio_->PlayStep();
	}
	if (Input::GetKey(Input::KEY_S)) {
		movement_vector_ = movement_vector_ - camera_->GetViewDirection();
		audio_->PlayStep();
	}
	if (Input::GetMousePressed(Input::LEFT_MOUSE)) {
		material_->SetTexture(animations_[2]);
		shot_ = true;
		audio_->PlayPlayerGunshot();
		glm::vec3 line_origin = glm::vec3(camera_->GetPosition().x, 0, camera_->GetPosition().z);
		glm::vec3 line_direction = glm::normalize(glm::vec3(camera_->GetViewDirection().x, 0, camera_->GetViewDirection().z));
		glm::vec3 line_end = line_origin + (line_direction * SHOOT_DISTANCE);
		Level::CheckIntersection(line_origin, line_end, true);
	}
	if (Input::GetKey(Input::KEY_ESCAPE)) {
		exit(1);
	}

	Input::SetMousePosition(glm::vec2(Window::GetWidth() / 2, Window::GetHeight() / 2));
}

void Player::Update()
{
	movement_vector_.y = 0;

	if (movement_vector_.length() > 0) {
		glm::normalize(movement_vector_);
	}

	old_position_ = camera_->GetPosition();
	new_position_ = old_position_ + (movement_vector_ * MOVEMENT_SPEED);
	collision_vector_ = Level::CheckCollision(old_position_, new_position_, SIZE, SIZE);
	
	movement_vector_ *= collision_vector_;

	camera_->MoveCamera(movement_vector_, MOVEMENT_SPEED);

	transform_->SetTranslation(glm::vec3(camera_->GetPosition().x + camera_->GetViewDirection().x * 0.30f, 0.22f, camera_->GetPosition().z + camera_->GetViewDirection().z * 0.29f));
	glm::vec3 camera_direction(transform_->GetCamera()->GetPosition().x - transform_->GetTranslation().x, transform_->GetCamera()->GetPosition().y, transform_->GetCamera()->GetPosition().z - transform_->GetTranslation().z);
	float camera_angle = -atanf(camera_direction.z / camera_direction.x) + (90.0f * M_PI / 180.0f);

	if (camera_direction.x > 0) {
		camera_angle += M_PI;
	}
	else {
	}
	transform_->SetRotation(0, camera_angle, 0);

	// 2 
	transform_2->SetTranslation(glm::vec3(camera_->GetPosition().x + camera_->GetViewDirection().x * 0.30f + 0.05, 0.52f, camera_->GetPosition().z + camera_->GetViewDirection().z * 0.29f));
	transform_2->SetRotation(0, camera_angle, 0);

	transform_3->SetTranslation(glm::vec3(camera_->GetPosition().x + camera_->GetViewDirection().x * 0.30f + 0.0, 0.52f, camera_->GetPosition().z + camera_->GetViewDirection().z * 0.29f));
	transform_3->SetRotation(0, camera_angle, 0);

	transform_4->SetTranslation(glm::vec3(camera_->GetPosition().x + camera_->GetViewDirection().x * 0.30f - 0.05, 0.52f, camera_->GetPosition().z + camera_->GetViewDirection().z * 0.29f));
	transform_4->SetRotation(0, camera_angle, 0);

	if (GetHealth() < 100) {
		int tens = GetHealth() / 10;
		int ones = GetHealth() % 10;
		material_2 = new Material(animations_2[0]);
		material_3 = new Material(animations_2[tens]);
		material_4 = new Material(animations_2[ones]);		
	}
}

int Player::GetHealth() {
	return health_;
}

void Player::Render()
{
	shader_ = Level::GetShader();
	shader_->UpdateUniforms(transform_2->GetModelProjection(), material_2);
	mesh_.Draw();
	shader_->UpdateUniforms(transform_3->GetModelProjection(), material_3);
	mesh_.Draw();
	shader_->UpdateUniforms(transform_4->GetModelProjection(), material_4);
	mesh_.Draw();
	shader_->UpdateUniforms(transform_->GetModelProjection(), material_);
	mesh_.Draw();

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
	vertices.push_back(Vertex(glm::vec3(-LENGTH / 2, y_coord, z_coord), glm::vec2(texture_coords[0], texture_coords[2])));
	vertices.push_back(Vertex(glm::vec3(-LENGTH / 2, HEIGHT, z_coord), glm::vec2(texture_coords[0], texture_coords[3])));
	vertices.push_back(Vertex(glm::vec3(LENGTH / 2, HEIGHT, z_coord), glm::vec2(texture_coords[1], texture_coords[3])));
	vertices.push_back(Vertex(glm::vec3(LENGTH / 2, y_coord, z_coord), glm::vec2(texture_coords[1], texture_coords[2])));
}

std::vector<float> Player::CalculateTextureCoords(int texture_number)
{
	float texture_x = texture_number % NUM_TEXTURES_X;
	float texture_y = texture_number / NUM_TEXTURES_X;
	std::vector<float> texture_coords;

	texture_coords.push_back((1.0f / NUM_TEXTURES_X) + (1.0f / NUM_TEXTURES_X) * texture_x);
	texture_coords.push_back((texture_coords[0] - (1.0f / NUM_TEXTURES_X)));
	texture_coords.push_back((1.0f / NUM_TEXTURES_Y) + (1.0f / NUM_TEXTURES_Y) * texture_y);
	texture_coords.push_back((texture_coords[2] - (1.0f / NUM_TEXTURES_Y)));

	return texture_coords;
}