#pragma once

#include "Camera.h"

#include <GLM/glm.hpp>
#include <GLM/gtc\matrix_transform.hpp>

class Transform
{
public:

	Transform();

	Camera* GetCamera() { return camera_; };
	void SetCamera(Camera* camera) { camera_ = camera; };

	glm::vec3 GetTranslation() { return translation_; };
	void SetTranslation(glm::vec3 translation) { translation_ = translation; };
	void SetTranslation(float x, float y, float z);

	glm::vec3 GetRotation() { return rotation_; };
	void SetRotation(glm::vec3 rotation) { rotation_ = rotation; };
	void SetRotation(float x, float y, float z);

	glm::vec3 GetScale() { return scale_; };
	void SetScale(glm::vec3 scale) { scale_ = scale; };
	void SetScale(float x, float y, float z);

	glm::mat4 GetModelMatrix();
	glm::mat4 GetModelProjection();

	void SetProjection(float fov, int width, int height, float near_plane, float far_plane);

private:

	float fov_;
	float width_;
	float height_;
	float near_plane_;
	float far_plane_;
	
	glm::vec3 translation_;
	glm::vec3 rotation_;
	glm::vec3 scale_;

	Camera* camera_;
};