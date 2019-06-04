#include "Camera.h"
#include "WindowManager.h"

#include <GLM/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 const& position, glm::vec3 const& rotation)
{
	m_Transform.SetPosition(position);
	m_Transform.SetRotation(rotation);
}

void Camera::MoveCamera(glm::vec3 const& movement_vector, float speed)
{
	m_Transform.Translate(movement_vector * speed);
	m_bViewHasChanged = true;
}

void Camera::MouseControl(float mouse_x, float mouse_y)
{
	glm::vec3 current_rotation = m_Transform.GetRotation();
	m_Transform.Rotate(mouse_y * 0.001f, mouse_x * 0.001f, 0);
	m_bViewHasChanged = true;
}

glm::vec3 Camera::GetPosition() const
{
	return m_Transform.GetPosition();
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
	glm::vec3 current_rotation = m_Transform.GetRotation();
	glm::mat4 rotation_matrix(1.0f);
	rotation_matrix = rotate(rotation_matrix, current_rotation.x, glm::vec3(1, 0, 0));
	rotation_matrix = rotate(rotation_matrix, current_rotation.y, glm::vec3(0, 1, 0));

	return rotation_matrix;
}

glm::mat4& Camera::GetViewMatrix()
{
	if (m_bViewHasChanged)
	{
		m_ViewMatrix = GetRotationMatrix() * glm::inverse(glm::translate(glm::mat4(), m_Transform.GetPosition()));
	}

	return m_ViewMatrix;
}

glm::mat4& Camera::GetProjectionMatrix()
{
	if (m_bProjectionHasChanged)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(70.0f), (float)(WindowManager::Get()->GetWidth() / WindowManager::Get()->GetHeight()), 0.1f, 1000.0f);
	}

	return m_ProjectionMatrix;
}