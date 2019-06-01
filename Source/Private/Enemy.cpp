#include "Enemy.h"
#include "ResourceManager.h"

const float SCALE = 0.73f;
const float LENGTH = 1.0f;
const float HEIGHT = 1.0f;

const float BODY_WIDTH = 0.2f;
const float BODY_LENGTH = 0.2f;
const float MOVEMENT_SPEED = 0.01f;
const float STOP_DISTANCE = 3.0f;

const float WEAPON_RANGE = 100.0f;
const float WEAPON_ANGLE = 10.0f;
const float ATTACK_CHANCE = 0.5f;
const int DAMAGE_AMOUNT = 6;

const int IDLE_STATE = 0;
const int CHASE_STATE = 1;
const int ATTACK_STATE = 2;
const int HURT_STATE = 3;
const int DEATH_STATE = 4;

const int HIT_POINTS = 100;

const int NUM_TEXTURES_X = 1;
const int NUM_TEXTURES_Y = 1;

Enemy::Enemy(glm::vec3 position)
{
	hp_ = HIT_POINTS;
	death_time_ = 0;
	hurt_time_ = 0;
	state_ = IDLE_STATE;
	dead_ = false;
	can_look_ = false;
	can_attack_ = false;

	audio_ = new Audio();
	position_ = position;

	m_Shader = ResourceManager::Get()->GetResource<Shader>("DefaultShader");

	transform_ = new Transform();
	transform_->SetTranslation(position_);
	transform_->SetScale(glm::vec3(SCALE, SCALE, SCALE));
	transform_->SetCamera(Player::GetCamera());

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// Idle
	animations_.push_back(new Texture("Enemy/pngs/mguard_s_1.png")); //0

	// Walk
	animations_.push_back(new Texture("Enemy/pngs/mguard_w1_1.png")); //1
	animations_.push_back(new Texture("Enemy/pngs/mguard_w2_1.png")); //2
	animations_.push_back(new Texture("Enemy/pngs/mguard_w3_1.png")); //3
	animations_.push_back(new Texture("Enemy/pngs/mguard_w4_1.png")); //4

	// Attack
	animations_.push_back(new Texture("Enemy/pngs/mguard_shoot1.png")); //5
	animations_.push_back(new Texture("Enemy/pngs/mguard_shoot2.png")); //6
	animations_.push_back(new Texture("Enemy/pngs/mguard_shoot3.png")); //7

	// Hurt
	animations_.push_back(new Texture("Enemy/pngs/mguard_pain1.png")); //8
	animations_.push_back(new Texture("Enemy/pngs/mguard_pain2.png")); //9

	// Death
	animations_.push_back(new Texture("Enemy/pngs/mguard_die1.png")); //10
	animations_.push_back(new Texture("Enemy/pngs/mguard_die2.png")); //11
	animations_.push_back(new Texture("Enemy/pngs/mguard_die3.png")); //12
	animations_.push_back(new Texture("Enemy/pngs/mguard_die4.png")); //13

	material_ = new Material(animations_[5]);
	AddIndices(indices, vertices.size(), false);
	AddVertices(vertices, false, 0, 0, 0, CalculateTextureCoords(27));

	mesh_.InitializeMesh(vertices, indices);
}

void Enemy::Idle(glm::vec3 orientation, float distance)
{
	material_->SetTexture(animations_[0]);

	glm::vec3 line_origin = transform_->GetTranslation();
	glm::vec3 line_direction = orientation;
	glm::vec3 line_end = line_origin + (line_direction * 100.0f);

	glm::vec3 collision_vector = Level::CheckIntersection(line_origin, line_end, false);
	glm::vec3 player_collision = Level::LineIntersectionRectangle(line_origin, line_end, glm::vec3(Player::GetCamera()->GetPosition().x, 0, Player::GetCamera()->GetPosition().z), 0.2f, 0.2f);

	if (player_collision != glm::vec3(NULL) && collision_vector == glm::vec3(NULL) ||
		glm::length(player_collision - line_origin) < glm::length(collision_vector - line_origin)) {
		state_ = CHASE_STATE;
	}
}

void Enemy::Chase(glm::vec3 orientation, float distance)
{
	double time = TimeManager::GetTime() - (int)TimeManager::GetTime();

	if (distance > STOP_DISTANCE) {
		if (time < 0.25f) {
			material_->SetTexture(animations_[1]);
		}
		else if (time < 0.50f) {
			material_->SetTexture(animations_[2]);
		}
		else if (time < 0.75f) {
			material_->SetTexture(animations_[3]);
		}
		else if (time < 1.00f) {
			material_->SetTexture(animations_[4]);
		}
		else {
		}

		glm::vec3 old_position = transform_->GetTranslation();
		glm::vec3 new_position = transform_->GetTranslation() + (orientation * MOVEMENT_SPEED);
		glm::vec3 collision_vector = Level::CheckCollision(old_position, new_position, BODY_WIDTH, BODY_LENGTH);

		glm::vec3 movement_vector = collision_vector * orientation;

		if (glm::length(movement_vector) > 0) {
			transform_->SetTranslation(transform_->GetTranslation() + (movement_vector * MOVEMENT_SPEED));
			audio_->PlayStep();
		}
	}
	else {
		state_ = ATTACK_STATE;
	}
}

void Enemy::Attack(glm::vec3 orientation, float distance)
{
	double time = TimeManager::GetTime() - (int)TimeManager::GetTime();

	if (time < 0.40f) {
		can_attack_ = true;
		material_->SetTexture(animations_[5]);
	}
	else if (time < 0.80f) {
		material_->SetTexture(animations_[6]);
	}
	else if (time < 1.00f) {
		if (can_attack_) {
			audio_->PlayEnemyGunshot();
			material_->SetTexture(animations_[7]);
			std::random_device generator;
			std::uniform_real_distribution<float> distribution(0.0f, 10.0f);
			float random = distribution(generator);

			glm::vec3 line_origin = transform_->GetTranslation();
			glm::vec3 line_direction = orientation;
			glm::vec3 line_end = line_origin + (line_direction * 100.0f);

			glm::vec3 collision_vector = Level::CheckIntersection(line_origin, line_end, false);
			glm::vec3 player_collision = Level::LineIntersectionRectangle(line_origin, line_end, glm::vec3(Player::GetCamera()->GetPosition().x, 0, Player::GetCamera()->GetPosition().z), 0.2f, 0.2f);

			if (player_collision != glm::vec3(NULL) && collision_vector == glm::vec3(NULL) ||
				glm::length(player_collision - line_origin) < glm::length(collision_vector - line_origin)) {
				Player::Damage(DAMAGE_AMOUNT);
				
				state_ = CHASE_STATE;
			}
			can_attack_ = false;
		}
		else {
			state_ = CHASE_STATE;
			material_->SetTexture(animations_[5]);
			can_attack_ = true;
		}
	}
	else {
	}
}

void Enemy::Damage(int damage_points)
{
	if (state_ = IDLE_STATE) {
		state_ = CHASE_STATE;
	}

	hp_ -= damage_points;

	if (hp_ > 0) {
		state_ = HURT_STATE;
	}
	else if (hp_ <= 0) {
		audio_->PlayEnemyDeath();
		state_ = DEATH_STATE;
	}
	else {
	}
}

void Enemy::Hurt(glm::vec3 orientation, float distance)
{
	material_->SetTexture(animations_[8]);

	state_ = ATTACK_STATE;
}

void Enemy::Death(glm::vec3 orientation, float distance)
{
	material_->SetTexture(animations_[13]);

}

void Enemy::FaceCamera(glm::vec3 orientation)
{
	float camera_angle = -atanf(orientation.z / orientation.x) + (90.0f * glm::pi<float>() / 180.0f);

	if (orientation.x > 0) {
		camera_angle += glm::pi<float>();
	}
	else {
	}

	transform_->SetRotation(0, camera_angle, 0);
}

void Enemy::Update()
{
	glm::vec3 camera_direction(transform_->GetCamera()->GetPosition().x - transform_->GetTranslation().x, 0, transform_->GetCamera()->GetPosition().z - transform_->GetTranslation().z);
	float camera_distance = glm::length(camera_direction);

	glm::vec3 camera_orientation = camera_direction / camera_distance;
	
	FaceCamera(camera_orientation);

	switch(state_) {
		case IDLE_STATE:
			Idle(camera_orientation, camera_distance);
			break;
		case CHASE_STATE:
			Chase(camera_orientation, camera_distance);
			break;
		case ATTACK_STATE:
			Attack(camera_orientation, camera_distance);
			break;
		case HURT_STATE:
			Hurt(camera_orientation, camera_distance);
			break;
		case DEATH_STATE:
			Death(camera_orientation, camera_distance);
			break;
	}
}

void Enemy::Render()
{
	m_Shader->Use();
	material_->GetTexture().Bind();
	m_Shader->SetMat4("transform", transform_->CalculateMVP());
	mesh_.Draw();
}

void Enemy::AddIndices(std::vector<unsigned int>& indices, int start, bool direction)
{
	indices.push_back(start + 0);
	indices.push_back(start + 1);
	indices.push_back(start + 2);

	indices.push_back(start + 0);
	indices.push_back(start + 2);
	indices.push_back(start + 3);

}

void Enemy::AddVertices(std::vector<Vertex>& vertices, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords)
{
	vertices.push_back(Vertex{ glm::vec3(-LENGTH / 2, y_coord, z_coord), glm::vec2(texture_coords[0], texture_coords[2]) });
	vertices.push_back(Vertex{ glm::vec3(-LENGTH / 2, HEIGHT, z_coord), glm::vec2(texture_coords[0], texture_coords[3]) });
	vertices.push_back(Vertex{ glm::vec3(LENGTH / 2, HEIGHT, z_coord), glm::vec2(texture_coords[1], texture_coords[3]) });
	vertices.push_back(Vertex{ glm::vec3(LENGTH / 2, y_coord, z_coord), glm::vec2(texture_coords[1], texture_coords[2]) });
}

std::vector<float> Enemy::CalculateTextureCoords(int texture_number)
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

glm::vec2 Enemy::GetSize()
{
	return glm::vec2(BODY_WIDTH, BODY_LENGTH);
}