#include "Camera.h"
#include "Input.h"
#include "Time.h"
#include "Window.h"

Camera::Camera(glm::vec3 position, float yaw, float pitch) :
	position_(position), yaw_(yaw), pitch_(pitch)
{
}

glm::vec3 Camera::GetRightDirection() const
{
	glm::vec4 right_vector = inverse(GetRotationMatrix()) * glm::vec4(1, 0, 0, 1);

	return glm::vec3(right_vector);
}

glm::vec3 Camera::GetViewDirection() const
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

glm::mat4 Camera::GetRotationMatrix() const
{
	glm::mat4 rotation_matrix(1.0f);
	rotation_matrix = rotate(rotation_matrix, pitch_, glm::vec3(1, 0, 0));
	rotation_matrix = rotate(rotation_matrix, yaw_, glm::vec3(0, 1, 0));

	return rotation_matrix;
}

glm::mat4 Camera::GetViewMatrix() const
{
	return GetRotationMatrix() * glm::inverse(glm::translate(glm::mat4(), position_));
}

void Camera::Input()
{
	// Camera Mouse Look
	float sensitivity = 0.5f;
	float move_amount = static_cast<float>(10 * Time::GetDelta());
	float rotation_amount = static_cast<float>(100 * Time::GetDelta());

	glm::vec2 centerPosition = glm::vec2((float)Window::GetWidth() / 2.0f, (float)Window::GetHeight() / 2.0f);
	glm::vec2 deltaPos = glm::vec2(Input::GetMousePosition()) - centerPosition;

	//TODO use deltatime
	if (Input::GetMousePosition().x != Window::GetWidth()/2 && Input::GetMousePosition().y != Window::GetHeight()/2) 
	{
		MouseControl(Input::GetMousePosition().x - Window::GetWidth()/2, Input::GetMousePosition().y - Window::GetHeight()/2);
	}

	if (Input::GetKey(Input::KEY_A)) {
		StrafeCamera(-0.1f);
	}
	if (Input::GetKey(Input::KEY_D)) {
		StrafeCamera(0.1f);
	}
	if (Input::GetKey(Input::KEY_W)) {
		MoveCamera(0.1f);
	}
	if (Input::GetKey(Input::KEY_S)) {
		MoveCamera(-0.1f);
	}
	if (Input::GetKey(Input::KEY_ESCAPE)) {
		Window::Destroy();
	}

	Input::SetMousePosition(glm::vec2(Window::GetWidth()/2, Window::GetHeight()/2));
}