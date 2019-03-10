#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"
#include "XMLParser.h"
#include "Node.h"
#include "Door.h"
#include "Enemy.h"
#include "Medkit.h"
#include "Audio.h"

//#include <SFML/Audio.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <string>

class Door;
class Enemy;
class Player;
class Medkit;

class Level
{
public:

	Level() {};
	Level(std::string filename, std::string texturefilename, Player* player);

	void Input();
	void Update();
	void Render();

	Audio* audio_;
	static Shader* GetShader();

	void OpenDoors(glm::vec3 position, bool exit);

	static glm::vec3 CheckCollision(glm::vec3 old_position, glm::vec3 new_position, float width, float length);
	static glm::vec3 RectangularCollision(glm::vec3 old_position, glm::vec3 new_position, glm::vec3 size_1, glm::vec3 position_2, glm::vec3 size_2);
	static glm::vec3 CheckIntersection(glm::vec3 line_start, glm::vec3 line_end, bool attack);
	static glm::vec3 LineIntersection(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 line_start2, glm::vec3 line_end2);
	static glm::vec3 LineIntersectionRectangle(glm::vec3 line_start, glm::vec3 line_end, glm::vec3 position, float width, float length);
	static glm::vec3 NearestIntersection(glm::vec3 line_1, glm::vec3 line_2, glm::vec3 nearest);

private:

	Player* player_;
	Camera* camera_;
	Transform* transform_;
	XMLParser* xml_parser_;
	Material* material_;
	Mesh mesh_;
	Enemy* enemy_;

	//sf::Music music;

	std::vector<Door> doors_;
	std::vector<Enemy> enemies_;
	std::vector<Medkit> medkits_;
	std::vector<glm::vec3> endpoints_;

	void AddIndices(std::vector<unsigned int>& indices, int start, bool direction);
	void AddVertices(std::vector<Vertex>& vertices, std::string type, bool invert, float x_coord, float y_coord, float z_coord, std::vector<float> texture_coords);
	std::vector<float> CalculateTextureCoords(int texture_number);
	void AddDoor(glm::vec3 position, bool x_orientation, bool y_orientation);

	void GenerateLevel();
	void RemoveMedkit();
};

#endif;