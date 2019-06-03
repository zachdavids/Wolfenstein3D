#pragma once

#include "Level.h"
#include "Transform.h"
#include "AudioManager.h"

class Medkit
{
public:

	Medkit(glm::vec3 position);

	void Update();
	void Render();
	bool GetEaten() { return eaten_; };

private:

	bool eaten_;

	glm::vec3 position_;
	Transform* transform_;
};