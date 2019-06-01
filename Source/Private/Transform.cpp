#include "Transform.h"

Transform::Transform()
{
	translation_ = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
	scale_ = glm::vec3(1.0f, 1.0f, 1.0f);
	fov_ = glm::radians(70.0f);
	width_ = Window::GetWidth();
	height_ = Window:: GetHeight();
	near_plane_ = 0.1f;
	far_plane_ = 1000.0f;
}

void Transform::SetTranslation(float x, float y, float z)
{
	translation_ = glm::vec3(x, y, z);
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation_ = glm::vec3(x, y, z);
}

void Transform::SetScale(float x, float y, float z)
{
	scale_ = glm::vec3(x, y, z);
}

glm::mat4 Transform::GetModelMatrix()
{
	// Translate
	glm::mat4 model_matrix = translate(glm::mat4(1.0f), translation_);

	// Scale
	model_matrix = scale(model_matrix, scale_);

	// Rotate
	model_matrix = rotate(model_matrix, rotation_.x, glm::vec3(1, 0, 0));
	model_matrix = rotate(model_matrix, rotation_.y, glm::vec3(0, 1, 0));
	model_matrix = rotate(model_matrix, rotation_.z, glm::vec3(0, 0, 1));

	return model_matrix;
}

glm::mat4 Transform::GetModelProjection()
{
	glm::mat4 model_matrix = GetModelMatrix();
	glm::mat4 projection_matrix = glm::perspective(fov_, (float)(width_/height_), near_plane_, far_plane_);
	glm::mat4 view_matrix = camera_->GetViewMatrix();

	return projection_matrix * view_matrix * model_matrix;
}

void Transform::SetProjection(float fov, int width, int height, float near_plane, float far_plane)
{
	width_ = (float)width;
	height_ = (float)height;
	near_plane_ = near_plane;
	far_plane_ = far_plane;
	fov_ = fov;
}