#ifndef CAMERA_H
#define CAMERA_H

#include "Input.h"
#include "Time.h"
#include "WindowManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:

	Camera();
	Camera(glm::vec3 position, float yaw, float pitch);

	glm::vec3 GetPosition() { return position_; };
	void SetPosition(glm::vec3 position) { position_ = position; };

	float GetYaw() { return yaw_; };
	void SetYaw(float yaw) { yaw_ = yaw; };

	float GetPitch() { return pitch_; };
	void SetPitch(float pitch) { pitch_ = pitch; };

	glm::vec3 GetRightDirection();
	glm::vec3 GetViewDirection();

	void MoveCamera(float speed);
	void MoveCamera(glm::vec3 movement_vector, float speed);
	void StrafeCamera(float speed);
	void Camera::MouseControl(float mouse_x, float mouse_y);

	glm::mat4 GetRotationMatrix();
	glm::mat4 GetViewMatrix();

	// TEST
	void Input();

private:

	float yaw_;
	float pitch_;

	glm::vec3 position_;
};

#endif;