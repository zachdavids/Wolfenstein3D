#include "Camera.h"
#include "WindowManager.h"

#include <GLM/gtc/matrix_transform.hpp>

const float Camera::m_FOV = glm::radians(70.0f);
const float Camera::m_Near = 0.1f;
const float Camera::m_Far = 1000.0f;

Camera::Camera(glm::vec3 const& position, glm::vec3 const& rotation)
{
	SetPosition(position);
	SetRotation(rotation);
}

void Camera::MoveCamera(glm::vec3 const& movement_vector, float speed)
{
	Translate(movement_vector * speed);
	m_bViewHasChanged = true;
}

void Camera::MouseControl(float mouse_x, float mouse_y)
{
	Rotate(glm::vec3(0, mouse_x * 0.001f, 0));
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
		float aspect_ratio = (float)(WindowManager::Get()->GetWidth() / WindowManager::Get()->GetHeight());
		m_ProjectionMatrix = glm::perspective(m_FOV, aspect_ratio, m_Near, m_Far);
	}

	return m_ProjectionMatrix;
}