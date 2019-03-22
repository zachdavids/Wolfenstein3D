#pragma once

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

class Camera
{
public:

	Camera(glm::vec3 position, float yaw, float pitch);

	glm::vec3 GetPosition() const { return position_; };
	void SetPosition(glm::vec3 position) { position_ = position; };

	float GetYaw() const { return yaw_; };
	void SetYaw(float yaw) { yaw_ = yaw; };

	float GetPitch() const { return pitch_; };
	void SetPitch(float pitch) { pitch_ = pitch; };

	glm::vec3 GetRightDirection() const;
	glm::vec3 GetViewDirection() const;
	glm::mat4 GetRotationMatrix() const;
	glm::mat4 GetViewMatrix() const;

	void MoveCamera(float speed);
	void MoveCamera(glm::vec3 movement_vector, float speed);
	void StrafeCamera(float speed);
	void Camera::MouseControl(float mouse_x, float mouse_y);

	// TEST
	void Input();

private:

	float yaw_ = 0;
	float pitch_ = 0;

	glm::vec3 position_ = glm::vec3(0);
};