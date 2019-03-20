#include "Transform.h"
#include "Camera.h"

Transform::Transform() : width_(Window::GetWidth()), height_(Window::GetHeight())
{
}

glm::mat4 Transform::GetModelMatrix()
{
	// Translate
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), translation_);

	// Scale
	model_matrix = glm::scale(model_matrix, scale_);

	// Rotate
	model_matrix = glm::rotate(model_matrix, rotation_.x, glm::vec3(1, 0, 0));
	model_matrix = glm::rotate(model_matrix, rotation_.y, glm::vec3(0, 1, 0));
	model_matrix = glm::rotate(model_matrix, rotation_.z, glm::vec3(0, 0, 1));

	return model_matrix;
}

glm::mat4 Transform::GetModelProjection()
{
	glm::mat4 model_matrix = GetModelMatrix();
	glm::mat4 projection_matrix = glm::perspective(fov_, static_cast<float>(width_ / height_), near_plane_, far_plane_);
	glm::mat4 view_matrix = camera_->GetViewMatrix();

	return projection_matrix * view_matrix * model_matrix;
}