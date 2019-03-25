#include "Level.h"

const int PLAYER_DAMAGE = 34;
const int NUM_TEXTURES_X = 6;
const int NUM_TEXTURES_Y = 19;
static glm::vec2 dimensions_;
static std::vector<Node> nodes_;
static std::vector<glm::vec3> collision_start;
static std::vector<glm::vec3> collision_end;
static int nearest_enemy_num;
static std::vector<Door> doors_temp_;
static std::vector<Enemy> enemies_temp_;
static Shader* shader_;

Level::Level(std::string filename, std::string texturefilename, Player* player)
{
	player_ = player;
	nearest_enemy_num = -1;
	xml_parser_ = new XMLParser("Resources/Levels/" + filename);

	audio_ = new Audio();
	material_ = new Material(new Texture(texturefilename));

	transform_ = new Transform();
	transform_->SetCamera(player_->GetCamera());

	shader_ = Shader::GetInstance();

	GenerateLevel();

	//music.openFromFile("Sounds/song.ogg");
	//music.setVolume(30);
	//music.setLoop(true);
	//music.play();
}

void Level::Input()
{
	if (Input::GetKey(Input::KEY_E)) 
	{
		OpenDoors(player_->GetCamera()->GetPosition(), true);
	}

	player_->Input();

	for (unsigned int i = 0; i < enemies_.size(); i++) 
	{
		OpenDoors(enemies_[i].GetTranslation(), false);
	}
}

void Level::Update()
{
	for (unsigned int i = 0; i < doors_.size(); i++) 
	{
		doors_[i].Update();
	}

	player_->Update();

	for (unsigned int i = 0; i < enemies_.size(); i++) 
	{
		enemies_[i].Update();
	}

	for (unsigned int i = 0; i < medkits_.size(); i++)
	{
		medkits_[i].Update();
	}

	if (nearest_enemy_num != -1) 
	{
		enemies_[nearest_enemy_num].Damage(PLAYER_DAMAGE);
		nearest_enemy_num = -1;
	}

	RemoveMedkit();
}

void Level::Render()
{
	shader_->Bind();
	shader_->UpdateUniforms(transform_->GetModelProjection(), material_);
	mesh_.Draw();

	for (unsigned int i = 0; i < doors_.size(); i++) {
		doors_[i].Render();
	}

	for (unsigned int i = 0; i < enemies_.size(); i++) {
		enemies_[i].Render();
	}

	for (unsigned int i = 0; i < medkits_.size(); i++) {
		medkits_[i].Render();
	}

	player_->Render();
}

void Level::AddIndices(std::vector<unsigned int>& indices, int start, bool direction)
{
	if (direction) {
		indices.push_back(start + 2);
		indices.push_back(start + 1);
		indices.push_back(start + 0);

		indices.push_back(start + 3);
		indices.push_back(start + 2);
		indices.push_back(start + 0);
	}
	else {
		indices.push_back(start + 0);
		indices.push_back(start + 1);
		indices.push_back(start + 2);

		indices.push_back(start + 0);
		indices.push_back(start + 2);
		indices.push_back(start + 3);
	}
}

void Level::AddVertices(std::vector<Vertex>& vertices, std::string type, bool invert, int x_coord, int y_coord, int z_coord, std::vector<float> texture_coords)
{
	if (type == "Floor" || type == "Ceiling")
	{
		vertices.push_back(Vertex(glm::vec3(x_coord, y_coord, z_coord), glm::vec2(texture_coords[1], texture_coords[2])));
		vertices.push_back(Vertex(glm::vec3(x_coord + 1, y_coord, z_coord), glm::vec2(texture_coords[0], texture_coords[2])));
		vertices.push_back(Vertex(glm::vec3(x_coord + 1, y_coord, z_coord + 1), glm::vec2(texture_coords[0], texture_coords[3])));
		vertices.push_back(Vertex(glm::vec3(x_coord, y_coord, z_coord + 1), glm::vec2(texture_coords[1], texture_coords[3])));
	}
	else if (type == "Wall")
	{
		if (!invert) 
		{
			vertices.push_back(Vertex(glm::vec3( x_coord, y_coord, z_coord), glm::vec2(texture_coords[1], texture_coords[2])));
			vertices.push_back(Vertex(glm::vec3(x_coord + 1, y_coord, z_coord), glm::vec2(texture_coords[0], texture_coords[2])));
			vertices.push_back(Vertex(glm::vec3(x_coord + 1, y_coord + 1 , z_coord), glm::vec2(texture_coords[0], texture_coords[3])));
			vertices.push_back(Vertex(glm::vec3( x_coord, y_coord + 1, z_coord), glm::vec2(texture_coords[1], texture_coords[3])));
		}
		else 
		{
			vertices.push_back(Vertex(glm::vec3(x_coord, y_coord, z_coord), glm::vec2(texture_coords[1], texture_coords[2])));
			vertices.push_back(Vertex(glm::vec3(x_coord, y_coord, z_coord + 1), glm::vec2(texture_coords[0], texture_coords[2])));
			vertices.push_back(Vertex(glm::vec3(x_coord, y_coord + 1, z_coord + 1), glm::vec2(texture_coords[0], texture_coords[3])));
			vertices.push_back(Vertex(glm::vec3(x_coord, y_coord + 1,  z_coord), glm::vec2(texture_coords[1], texture_coords[3])));
		}
	}
}

std::vector<float> Level::CalculateTextureCoords(int texture_number)
{
	float texture_x = static_cast<float>(texture_number % NUM_TEXTURES_X);
	float texture_y = static_cast<float>(texture_number / NUM_TEXTURES_X);

	std::vector<float> texture_coords;
	texture_coords.push_back((1.0f / NUM_TEXTURES_X) + (1.0f / NUM_TEXTURES_X) * texture_x);
	texture_coords.push_back((texture_coords[0] - (1.0f / NUM_TEXTURES_X)));
	texture_coords.push_back((1.0f / NUM_TEXTURES_Y) + (1.0f / NUM_TEXTURES_Y) * texture_y);
	texture_coords.push_back((texture_coords[2] - (1.0f / NUM_TEXTURES_Y)));
	return texture_coords;
}

void Level::AddDoor(glm::vec3 position, bool orientation) 
{
	if (orientation) 
	{
		doors_.push_back(Door(position, material_, glm::vec3(position.x + 0.9, position.y, position.z), false));
	}
	else 
	{
		doors_.push_back(Door(position, material_, glm::vec3(position.x, position.y, position.z + 0.9), true));
	}
	doors_temp_ = doors_;
}

void Level::OpenDoors(glm::vec3 position, bool exit)
{
	for (unsigned int i = 0; i < doors_.size(); i++)
	{
		if (glm::length(doors_[i].GetPosition() - position) < 1.0f) 
		{
			doors_[i].Open();
		}
	}
	if (exit)
	{
		for (unsigned int i = 0; i < endpoints_.size(); i++)
		{
			if (glm::length(endpoints_[i] - position) < 1.0f) 
			{
				audio_->PlayLevelEnd();
				Game::LoadNextLevel();
			}
		}
	}
}

void Level::GenerateLevel()
{
	dimensions_ = xml_parser_->GetDimensions();
	dimensions2_ = xml_parser_->GetDimensions();
	nodes_ = xml_parser_->GetNodes();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int z = 0; z < dimensions_.x; z++) 
	{
		for (unsigned int x = 0; x < dimensions_.y; x++) 
		{
			int current_index = GetFlatIndex(x, z);
			if (nodes_[current_index].IsType(Node::Location))
			{
				AddIndices(indices, vertices.size(), true);
				AddVertices(vertices, "Floor", false, x, 0, z, CalculateTextureCoords(0));
				AddIndices(indices, vertices.size(), false);
				AddVertices(vertices, "Ceiling", false, x, 1, z, CalculateTextureCoords(22));			

				if (!nodes_[GetFlatIndex(x - 1, z)].IsType(Node::Location))
				{
					AddIndices(indices, vertices.size(), true);
					AddVertices(vertices, "Wall", true, x, 0, z, CalculateTextureCoords(3));
					collision_start.push_back(glm::vec3(x, 0, z));
					collision_end.push_back(glm::vec3(x, 0, z + 1));
				}
				if (!nodes_[GetFlatIndex(x + 1, z)].IsType(Node::Location)) 
				{
					AddIndices(indices, vertices.size(), true);
					AddVertices(vertices, "Wall", true, x + 1, 0, z, CalculateTextureCoords(3));
					collision_start.push_back(glm::vec3(x, 0, z));
					collision_end.push_back(glm::vec3(x + 1, 0, z + 1));
				}
				if (!nodes_[GetFlatIndex(x, z - 1)].IsType(Node::Location)) 
				{
					AddIndices(indices, vertices.size(), false);
					AddVertices(vertices, "Wall", false, x, 0, z, CalculateTextureCoords(3));
					collision_start.push_back(glm::vec3(x , 0, z));
					collision_end.push_back(glm::vec3(x + 1, 0, z));
				}

				if (!nodes_[GetFlatIndex(x, z + 1)].IsType(Node::Location)) 
				{
					AddIndices(indices, vertices.size(), false);
					AddVertices(vertices, "Wall", false, x, 0, z + 1, CalculateTextureCoords(3));
					collision_start.push_back(glm::vec3(x, 0, z + 1));
					collision_end.push_back(glm::vec3(x + 1, 0, z + 1));
				}
			}
			if (nodes_[current_index].IsType(Node::Door)) 
			{
				bool orientation = ((!nodes_[GetFlatIndex(x - 1, z)].IsType(Node::Location)) &&
					(!nodes_[GetFlatIndex(x + 1, z)].IsType(Node::Location)));
				AddDoor(glm::vec3(x, 0, z), orientation);
			}
			if (nodes_[current_index].IsType(Node::Enemy)) 
			{
				enemies_.push_back(Enemy(glm::vec3(x, 0, z)));
			}
			if (nodes_[current_index].IsType(Node::Medkit)) 
			{
				medkits_.push_back(Medkit(glm::vec3(x, 0, z)));
			}
			if (nodes_[current_index].IsType(Node::Endpoint)) 
			{
				endpoints_.push_back(glm::vec3(x, 0, z));
			}
		}
	}
	enemies_temp_ = enemies_;
	mesh_.InitializeMesh(vertices, indices);
}

glm::vec3 Level::CheckCollision(glm::vec3 old_position, glm::vec3 new_position, float width, float length)
{
	glm::vec3 collision_vector = glm::vec3(1, 0, 1);
	glm::vec3 movement_vector = new_position - old_position;

	if (movement_vector.length() > 0) {
		// Wall Collision
		glm::vec3 node_size(1, 0, 1);
		glm::vec3 object_size(width, 0, length);

		glm::vec3 old_position_2(old_position.x + 1, 0, old_position.z);
		glm::vec3 new_position_2(new_position.x + 1, 0, new_position.z);

		//TODO fix x+1 in collision_vector
		for (int z = 0; z < dimensions_.y; z++) {
			for (int x = 0; x < dimensions_.x; x++) {
				if (!nodes_[dimensions_.y * z + x].IsType(Node::Location)) 
				{
					collision_vector *= RectangularCollision(old_position_2, new_position_2, object_size, node_size * glm::vec3(x + 1, 0, z), node_size);
				}
			}
		}

		// Door Collision
		old_position_2.x = old_position.x;
		new_position_2.x = new_position.x;

		for (unsigned int z = 0; z < doors_temp_.size(); z++) {
			node_size = doors_temp_[z].GetDimensions();
			collision_vector *= RectangularCollision(old_position_2, new_position_2, object_size, doors_temp_[z].GetTranslation(), node_size);
		}
	}

	return collision_vector;
}

glm::vec3 Level::RectangularCollision(glm::vec3 old_position, glm::vec3 new_position, glm::vec3 size_1, glm::vec3 position_2, glm::vec3 size_2)
{
	glm::vec3 result(0.0f);

	if ((new_position.x + size_1.x < position_2.x) || (new_position.x - size_1.x > position_2.x + size_2.x * size_2.x) ||
		(old_position.z + size_1.z < position_2.z) || (old_position.z - size_1.z > position_2.z + size_2.z * size_2.z)) {
		result.x = 1;
	}

	if ((old_position.x + size_1.x < position_2.x) || (old_position.x - size_1.x > position_2.x + size_2.x * size_2.x) ||
		(new_position.z + size_1.z < position_2.z) || (new_position.z - size_1.z > position_2.z + size_2.z * size_2.z)) {
		result.z = 1;
	}

	return result;
}

glm::vec3 Level::CheckIntersection(glm::vec3 line_start, glm::vec3 line_end, bool attack)
{
	glm::vec3 nearest_intersection(NULL);

	for (unsigned int i = 0; i < collision_start.size(); i++) {
		glm::vec3 collision_vector = LineIntersection(line_start, line_end, collision_start[i], collision_end[i]);

		if (collision_vector != glm::vec3(NULL) && nearest_intersection == glm::vec3(NULL) ||
			glm::length(nearest_intersection - line_start) > glm::length(collision_vector - line_start)) {
			nearest_intersection = NearestIntersection(nearest_intersection, collision_vector, line_start);
		}
	}

	for (unsigned int i = 0; i < doors_temp_.size(); i++) {
		glm::vec3 collision_vector = LineIntersectionRectangle(line_start, line_end, doors_temp_[i].GetTranslation(), doors_temp_[i].GetDimensions().x, doors_temp_[i].GetDimensions().y);

		if (collision_vector != glm::vec3(NULL) && nearest_intersection == glm::vec3(NULL) ||
			glm::length(nearest_intersection - line_start) > glm::length(collision_vector - line_start)) {
			nearest_intersection = NearestIntersection(nearest_intersection, collision_vector, line_start);
		}
	}

	if (attack) {
		glm::vec3 nearest_enemy_intersection(NULL);
		glm::vec3 collision_vector(NULL);
		Enemy nearest_enemy;

		for (unsigned int i = 0; i < enemies_temp_.size(); i++) {
			glm::vec3 collision_vector = LineIntersectionRectangle(line_start, line_end, enemies_temp_[i].GetTranslation(), enemies_temp_[i].GetSize().x, enemies_temp_[i].GetSize().y);

			glm::vec3 last_enemy_intersection = nearest_enemy_intersection;
			nearest_enemy_intersection = NearestIntersection(nearest_intersection, collision_vector, line_start);

			if (nearest_enemy_intersection == collision_vector) {
				nearest_enemy_num = i;
			}
			else {
			}
		}
	}

	return nearest_intersection;
}

glm::vec3 Level::LineIntersection(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 line_start2, glm::vec3 line_end2)
{
	glm::vec3 line_1 = line_end - line_start;
	glm::vec3 line_2 = line_end2 - line_start2;

	float cross = (line_1.x * line_2.z) - (line_1.z * line_2.x);

	if (cross == 0) {
		return glm::vec3(NULL);
	}

	glm::vec3 distance_between = line_start2 - line_start;

	float a = ((distance_between.x * line_2.z) - (distance_between.z * line_2.x)) / cross;
	float b = ((distance_between.x * line_1.z) - (distance_between.z * line_1.x)) / cross;

	if ((a > 0.0f && a < 1.0f) && (b > 0.0f && b < 1.0f)) {
		return line_start + (line_1 * a);
	}

	return glm::vec3(NULL);
}

glm::vec3 Level::LineIntersectionRectangle(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 position, float width, float length)
{
	glm::vec3 result = glm::vec3(NULL);

	glm::vec3 collision_vector = LineIntersection(line_start, line_end, position, glm::vec3(position.x + width, 0, position.z));
	result = NearestIntersection(result, collision_vector, line_start);

	collision_vector = LineIntersection(line_start, line_end, position, glm::vec3(position.x, 0, position.z + length));
	result = NearestIntersection(result, collision_vector, line_start);

	collision_vector = LineIntersection(line_start, line_end, glm::vec3(position.x, 0, position.z + length), glm::vec3(position.x + width, 0, position.z + length));
	result = NearestIntersection(result, collision_vector, line_start);

	collision_vector = LineIntersection(line_start, line_end, glm::vec3(position.x + width, 0, position.z), glm::vec3(position.x + width, 0, position.z + length));
	result = NearestIntersection(result, collision_vector, line_start);

	return result;
}

glm::vec3 Level::NearestIntersection(glm::vec3 line_1, glm::vec3 line_2, glm::vec3 nearest)
{
	if (line_2 != glm::vec3(NULL) && line_1 == glm::vec3(NULL) ||
		glm::length(line_1 - nearest) > glm::length(line_2 - nearest)) {
		return line_2;
	}
	else {
	}
	return line_1;
}
 
Shader* Level::GetShader() 
{ 
	return shader_; 
}

void Level::RemoveMedkit()
{
	for (unsigned int i = 0; i < medkits_.size(); i++) {
		if (medkits_[i].GetEaten()) {
			medkits_.erase(medkits_.begin() + i);
		}
	}
}
