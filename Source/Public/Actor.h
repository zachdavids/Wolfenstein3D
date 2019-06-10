#pragma once

#include "Transform.h"

#include <GLM/mat4x4.hpp>

class Actor
{
public:

	virtual void Update() {};
	virtual void Render() {};
	void Translate(glm::vec3 const& translation);
	void Rotate(glm::vec3 const& rotate);
	void Scale(glm::vec3 const& scale);
	glm::vec3& GetPosition();
	glm::vec3& GetRotation();
	glm::vec3& GetScale();
	glm::vec3 GetRight() const;
	glm::vec3 GetForward() const;
	glm::mat4 GetRotationMatrix() const;
	glm::mat4 GetModelMatrix() const;
	void SetPosition(glm::vec3 const& position);
	void SetRotation(glm::vec3 const& rotation);
	void SetScale(glm::vec3 const& scale);

private:

	Transform m_Transform;
};