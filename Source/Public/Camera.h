#pragma once

#include "Actor.h"

class Camera : public Actor
{
public:

	Camera(glm::vec3 const& position, glm::vec3 const& rotation);
	glm::vec3 GetPosition() const;
	glm::vec3 GetRight() const;
	glm::vec3 GetForward() const;
	glm::mat4& GetViewMatrix();
	glm::mat4& GetProjectionMatrix();
	void MoveCamera(glm::vec3 const& movement_vector, float speed);
	void MouseControl(float mouse_x, float mouse_y);

private:

	bool m_bViewHasChanged = true;
	bool m_bProjectionHasChanged = true;
	static const float m_FOV;
	static const float m_Near;
	static const float m_Far;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 GetRotationMatrix() const;
};