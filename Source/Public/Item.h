#pragma once

#include "Actor.h"

class Mesh;
class TextureArray;
class Shader;

class Item : public Actor
{
public:

	Item(glm::vec3 const& position, int t_id);
	void Update() override;
	void Render() override;

protected:

	int m_Tid;
	Shader* m_Shader;
	TextureArray* m_Texture;
	Mesh* m_Mesh;
};

