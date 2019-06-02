#include "Camera.h"

#include <GLM/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, float yaw, float pitch) :
	m_Position(position),
	m_Yaw(yaw),
	m_Pitch(pitch)
{
}

void Camera::MoveCamera(glm::vec3 movement_vector, float speed)
{
	glm::vec3 view_vector = movement_vector;

	m_Position.x += view_vector.x * speed;
	m_Position.y += view_vector.y * speed;
	m_Position.z += view_vector.z * speed;
}

void Camera::MouseControl(float mouse_x, float mouse_y)
{
	m_Yaw += mouse_x * 0.001f;
	m_Pitch += mouse_y * 0.001f;
}

glm::vec3 Camera::GetPosition() const
{
	return m_Position;
}

glm::vec3 Camera::GetRight() const
{
	glm::vec4 right_vector = inverse(GetRotationMatrix()) * glm::vec4(1, 0, 0, 1);

	return glm::vec3(right_vector);
}

glm::vec3 Camera::GetForward() const
{
	glm::vec4 view_vector = inverse(GetRotationMatrix()) * glm::vec4(0, 0, -1, 1);
	
	return glm::vec3(view_vector);
}

glm::mat4 Camera::GetRotationMatrix() const
{
	glm::mat4 rotation_matrix(1.0f);
	rotation_matrix = rotate(rotation_matrix, m_Pitch, glm::vec3(1, 0, 0));
	rotation_matrix = rotate(rotation_matrix, m_Yaw, glm::vec3(0, 1, 0));

	return rotation_matrix;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return GetRotationMatrix() * glm::inverse(glm::translate(glm::mat4(), m_Position));
}