#include "Actor.h"
#include "Shader.h"
#include "TextureArray.h"
#include "Mesh.h"

#include <GLM/gtc/matrix_transform.hpp>

glm::vec3& Actor::GetPosition()
{
	return m_Position;
}

glm::vec3& Actor::GetRotation()
{
	return m_Rotation;
}

glm::vec3& Actor::GetScale()
{
	return m_Scale;
}

void Actor::Render()
{
	m_Shader->Bind();
	m_Shader->SetMat4("model", GetModelMatrix());
	m_Shader->SetInt("index", m_Tid);
	m_Texture->Bind();
	m_Mesh->Draw();
}

void Actor::Translate(glm::vec3 const& translation)
{
	m_Position += translation;
}

void Actor::Rotate(glm::vec3 const& rotate)
{
	m_Rotation += rotate;
}

void Actor::Scale(glm::vec3 const& scale)
{
	m_Scale += scale;
}

glm::vec3 Actor::GetRight() const
{
	glm::vec4 right_vector = glm::inverse(GetRotationMatrix()) * glm::vec4(1, 0, 0, 1);

	return glm::vec3(right_vector);
}

glm::vec3 Actor::GetForward() const
{
	glm::vec4 view_vector = glm::inverse(GetRotationMatrix()) * glm::vec4(0, 0, -1, 1);

	return glm::vec3(view_vector);
}

glm::mat4 Actor::GetRotationMatrix() const
{
	glm::mat4 rotation_matrix(1.0f);
	rotation_matrix = glm::rotate(rotation_matrix, m_Rotation.x, glm::vec3(1, 0, 0));
	rotation_matrix = glm::rotate(rotation_matrix, m_Rotation.y, glm::vec3(0, 1, 0));

	return rotation_matrix;
}

glm::mat4 Actor::GetModelMatrix() const
{
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), m_Position);

	model_matrix = glm::scale(model_matrix, m_Scale);

	model_matrix = glm::rotate(model_matrix, m_Rotation.x, glm::vec3(1, 0, 0));
	model_matrix = glm::rotate(model_matrix, m_Rotation.y, glm::vec3(0, 1, 0));
	model_matrix = glm::rotate(model_matrix, m_Rotation.z, glm::vec3(0, 0, 1));

	return model_matrix;
}

void Actor::SetPosition(glm::vec3 const& position)
{
	m_Position = position;
}

void Actor::SetRotation(glm::vec3 const& rotation)
{
	m_Rotation = rotation;
}

void Actor::SetScale(glm::vec3 const& scale)
{
	m_Scale = scale;
}
