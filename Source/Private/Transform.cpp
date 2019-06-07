#include "Transform.h"
#include "WindowManager.h"
#include "Camera.h"

#include <GLM/gtc/matrix_transform.hpp>

void Transform::Translate(glm::vec3 translation)
{
	m_Position += translation;
}

void Transform::Translate(float x, float y, float z)
{
	Translate(glm::vec3(x, y, z));
}

void Transform::Rotate(glm::vec3 rotate)
{
	m_Rotation += rotate;
}

void Transform::Rotate(float roll, float yaw, float pitch)
{
	Rotate(glm::vec3(roll, yaw, pitch));
}

void Transform::Scale(glm::vec3 scale)
{
	m_Scale += scale;
}

void Transform::Scale(float x, float y, float z)
{
	Scale(glm::vec3(x, y, z));
}

void Transform::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}

void Transform::SetRotation(float x, float y, float z)
{
	m_Rotation = glm::vec3(x, y, z);
}

void Transform::SetScale(float x, float y, float z)
{
	m_Scale = glm::vec3(x, y, z);
}

glm::vec3 Transform::GetRight() const
{
	glm::vec4 right_vector = inverse(GetRotationMatrix()) * glm::vec4(1, 0, 0, 1);

	return glm::vec3(right_vector);
}

glm::vec3 Transform::GetForward() const
{
	glm::vec4 view_vector = inverse(GetRotationMatrix()) * glm::vec4(0, 0, -1, 1);

	return glm::vec3(view_vector);
}

glm::mat4 Transform::GetRotationMatrix() const
{
	glm::mat4 rotation_matrix(1.0f);
	rotation_matrix = rotate(rotation_matrix, m_Rotation.x, glm::vec3(1, 0, 0));
	rotation_matrix = rotate(rotation_matrix, m_Rotation.y, glm::vec3(0, 1, 0));

	return rotation_matrix;
}

glm::mat4 Transform::GetModelMatrix()
{
	glm::mat4 model_matrix = translate(glm::mat4(1.0f), m_Position);

	model_matrix = scale(model_matrix, m_Scale);

	model_matrix = rotate(model_matrix, m_Rotation.x, glm::vec3(1, 0, 0));
	model_matrix = rotate(model_matrix, m_Rotation.y, glm::vec3(0, 1, 0));
	model_matrix = rotate(model_matrix, m_Rotation.z, glm::vec3(0, 0, 1));

	return model_matrix;
}