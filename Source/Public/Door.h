#pragma once

#include "Level.h"
#include "Transform.h"
#include "Player.h"
#include "TimeManager.h"
#include "AudioManager.h"

#include <GLM/gtx\compatibility.hpp>

class Door
{
public:
	
	Door(glm::vec3 position, glm::vec3 open_position, bool rotation);

	void Open();

	void Update();
	void Render();

	glm::vec3 GetDimensions();
	glm::vec3 GetTranslation() { return transform_->GetTranslation(); };

	glm::vec3 GetPosition() { return position_; };
	void SetPosition(glm::vec3 position) { position_ = position; };

private:

	bool is_open_;
	double open_start_, open_time_;
	double close_start_, close_time_;

	glm::vec3 position_;
	glm::vec3 open_position_;
	glm::vec3 close_position_;

	Transform* transform_;
};