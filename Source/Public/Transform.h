#pragma once

#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>

class Camera;

class Transform
{
public:

	void Translate(glm::vec3 translation);
	void Translate(float x, float y, float z);
	void Rotate(glm::vec3 rotate);
	void Rotate(float roll, float yaw, float pitch);
	void Scale(glm::vec3 scale);
	void Scale(float x, float y, float z);

	Camera* GetCamera() { return m_Camera; };
	glm::vec3 GetPosition() const { return m_Position; };
	glm::vec3 GetRotation() const { return m_Rotation; };
	glm::vec3 GetScale() const { return m_Scale; };
	glm::mat4 GetModelMatrix();
	glm::mat4 GetModelProjection();

	void SetCamera(Camera* camera) { m_Camera = camera; };
	void SetPosition(glm::vec3 translation) { m_Position = translation; };
	void SetPosition(float x, float y, float z);
	void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; };
	void SetRotation(float x, float y, float z);
	void SetScale(glm::vec3 scale) { m_Scale = scale; };
	void SetScale(float x, float y, float z);

private:

	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Camera* m_Camera;
};