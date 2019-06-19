#pragma once

#include "Actor.h"

class Camera : public Actor
{
public:

	Camera(glm::vec3 const& position, glm::vec3 const& rotation);
	virtual void Update() override {};
	glm::mat4& GetViewMatrix();
	glm::mat4& GetProjectionMatrix();
	void Move(glm::vec3 const& movement);
	void Aim(float x);
	static constexpr float s_FOV = 70.0f;
	static constexpr float s_Near = 0.1f;
	static constexpr float s_Far = 1000.0f;

private:

	bool m_bViewHasChanged = true;
	bool m_bProjectionHasChanged = true;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
};