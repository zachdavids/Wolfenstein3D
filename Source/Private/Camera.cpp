#include "Camera.h"
#include "WindowManager.h"

#include <GLFW/glfw3.h>

Camera::Camera()
{
	position_ = glm::vec3(0, 0, 0);
	yaw_ = 0;
	pitch_ = 0;
}

Camera::Camera(glm::vec3 position, float yaw, float pitch)
{
	position_ = position;
	yaw_ = yaw;
	pitch_ = pitch;
}

glm::vec3 Camera::GetRightDirection()
{
	glm::vec4 right_vector = inverse(GetRotationMatrix()) * glm::vec4(1, 0, 0, 1);

	return glm::vec3(right_vector);
}

glm::vec3 Camera::GetViewDirection()
{
	glm::vec4 view_vector = inverse(GetRotationMatrix()) * glm::vec4(0, 0, -1, 1);
	
	return glm::vec3(view_vector);
}

void Camera::MoveCamera(float speed)
{
	glm::vec3 view_vector = GetViewDirection();

	position_.x += view_vector.x * speed;
	position_.y += view_vector.y * speed;
	position_.z += view_vector.z * speed;
}

void Camera::MoveCamera(glm::vec3 movement_vector, float speed)
{
	glm::vec3 view_vector = movement_vector;

	position_.x += view_vector.x * speed;
	position_.y += view_vector.y * speed;
	position_.z += view_vector.z * speed;
}


void Camera::MouseControl(float mouse_x, float mouse_y)
{
	yaw_ += mouse_x * 0.001f;
	pitch_ += mouse_y * 0.001f;
}

void Camera::StrafeCamera(float speed)
{
	glm::vec3 right_vector = GetRightDirection();

	position_.x += right_vector.x * speed;		
	position_.z += right_vector.z * speed;
}

glm::mat4 Camera::GetRotationMatrix()
{
	glm::mat4 rotation_matrix(1.0f);

	rotation_matrix = rotate(rotation_matrix, pitch_, glm::vec3(1, 0, 0));
	rotation_matrix = rotate(rotation_matrix, yaw_, glm::vec3(0, 1, 0));

	return rotation_matrix;
}

glm::mat4 Camera::GetViewMatrix()
{
	return GetRotationMatrix() * glm::inverse(glm::translate(glm::mat4(), position_));
}

void Camera::Input()
{
	// Camera Mouse Look
	float sensitivity = 0.5f;
	float movAmt = (float)(10 * TimeManager::GetDelta());
	float rotAmt = (float)(100 * TimeManager::GetDelta());

	double mouse_x;
	double mouse_y;
	glfwGetCursorPos(WindowManager::Get()->GetWindow(), &mouse_x, &mouse_y);

	float window_width = (float)WindowManager::Get()->GetWidth();
	float window_height = (float)WindowManager::Get()->GetHeight();

	if (mouse_x != window_width / 2.0f && mouse_y != window_height / 2.0f) {
		MouseControl(mouse_x - window_width / 2.0f, mouse_y - window_height / 2.0f);
	}

	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_A)) {
		StrafeCamera(-0.1f);
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_D)) {
		StrafeCamera(0.1f);
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_W)) {
		MoveCamera(0.1f);
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_S)) {
		MoveCamera(-0.1f);
	}
	if (glfwGetKey(WindowManager::Get()->GetWindow(), GLFW_KEY_ESCAPE)) {
		exit(1);
	}

	glfwSetCursorPos(WindowManager::Get()->GetWindow(), window_width / 2.0f, window_height / 2.0f);
}