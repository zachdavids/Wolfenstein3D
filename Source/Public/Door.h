#pragma once

#include "Actor.h"

class Door : public Actor
{
public:
	
	Door(glm::vec3 position, glm::vec3 open_position, bool rotation);
	void Open();
	virtual void Update() override;
	virtual void Render() override;
	glm::vec3 GetDimensions();
	glm::vec3 GetPosition() { return m_Transform.GetPosition(); };

private:

	bool is_open_;
	double open_start_;
	double open_time_;
	double close_start_;
	double close_time_;
	glm::vec3 open_position_;
	glm::vec3 close_position_;
};