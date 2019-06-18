#pragma once

#include <GLM/vec3.hpp>
#include <GLM/mat4x4.hpp>

class Mesh;
class TextureArray;
class Shader;

class Actor
{
public:

	Actor() = default;
	Actor(glm::vec3 position, glm::vec3 rotation, int t_id, Mesh* mesh, Shader* shader, TextureArray* texture);
	virtual void Update() {};
	virtual void Render();
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

protected:

	int m_Tid;
	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Mesh* m_Mesh = nullptr;
	Shader* m_Shader = nullptr;
	TextureArray* m_Texture = nullptr;
};