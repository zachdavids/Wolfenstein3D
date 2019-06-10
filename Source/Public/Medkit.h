#pragma once

#include "Actor.h"

class Mesh;
class Texture;
class Shader;

class Medkit : public Actor
{
public:

	Medkit(glm::vec3 const& position);
	virtual void Update() override;
	virtual void Render() override;
	bool GetEaten();

private:

	static const int m_HealAmount;
	static const float m_PickupDistance;
	bool m_bIsEaten = false;
	Shader* m_Shader;
	Texture* m_Texture;
	Mesh* m_Mesh;
};