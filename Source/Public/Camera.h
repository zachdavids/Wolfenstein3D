#pragma once

#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>

class Camera
{
public:

	Camera(glm::vec3 const& position, float yaw, float pitch);
	glm::vec3 GetPosition() const;
	glm::vec3 GetRight() const;
	glm::vec3 GetForward() const;
	glm::mat4 GetViewMatrix() const;
	void MoveCamera(glm::vec3 const& movement_vector, float speed);
	void MouseControl(float mouse_x, float mouse_y);

private:

	float m_Yaw;
	float m_Pitch;
	glm::vec3 m_Position;
	glm::mat4 GetRotationMatrix() const;
};