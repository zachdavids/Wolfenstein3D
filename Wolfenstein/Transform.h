#pragma once

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

class Camera;

class Transform
{
public:

	Transform();

	Camera* GetCamera() const { return camera_; };
	void SetCamera(Camera* camera) { camera_ = camera; };

	glm::vec3 GetTranslation() const { return translation_; };
	void SetTranslation(glm::vec3 translation) { translation_ = translation; };

	glm::vec3 GetRotation() const { return rotation_; };
	void SetRotation(glm::vec3 rotation) { rotation_ = rotation; };

	glm::vec3 GetScale() const { return scale_; };
	void SetScale(glm::vec3 scale) { scale_ = scale; };

	glm::mat4 GetModelMatrix();
	glm::mat4 GetModelProjection();

private:

	int width_;
	int height_;
	float fov_ = glm::radians(70.0f);
	float near_plane_ = 0.1f;
	float far_plane_ = 1000.0f;
	
	glm::vec3 translation_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale_ = glm::vec3(1.0f, 1.0f, 1.0f);

	//todo remove raw pointer
	Camera* camera_;
};