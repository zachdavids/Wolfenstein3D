#include "Camera.h"
#include "WindowManager.h"

#include <GLM/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 const& position, glm::vec3 const& rotation)
{
	m_Position = position;
	m_Rotation = rotation;
}

void Camera::Move(glm::vec3 const& movement)
{
	Translate(movement);
	m_bViewHasChanged = true;
}

void Camera::Aim(float x)
{
	Rotate(glm::vec3(0, x, 0));
	m_bViewHasChanged = true;
}

glm::mat4& Camera::GetViewMatrix()
{
	if (m_bViewHasChanged)
	{
		m_ViewMatrix = GetRotationMatrix() * glm::inverse(glm::translate(glm::mat4(), GetPosition()));
	}

	return m_ViewMatrix;
}

glm::mat4& Camera::GetProjectionMatrix()
{
	if (m_bProjectionHasChanged)
	{
		float aspect_ratio = (float)(WindowManager::Get()->s_Width / WindowManager::Get()->s_Height);
		m_ProjectionMatrix = glm::perspective(s_FOV, aspect_ratio, s_Near, s_Far);
	}

	return m_ProjectionMatrix;
}