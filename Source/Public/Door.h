#pragma once

#include "Actor.h"
#include "AABB.h"

class Shader;
class TextureArray;
class Mesh;

class Door : public Actor
{
public:
	
	Door(glm::vec3 const& position, glm::vec3 const& rotatiom, int t_id);
	void Open();
	virtual void Update() override;
	virtual void Render() override;
	AABB GetAABB();

private:

	int m_Tid;
	bool is_open_;
	double open_start_;
	double open_time_;
	double close_start_;
	double close_time_;
	Shader* m_Shader;
	TextureArray* m_Texture;
	Mesh* m_Mesh;
	glm::vec3 m_OpenPosition;
	glm::vec3 m_ClosePosition;
};