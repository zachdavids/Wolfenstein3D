#pragma once

#include "Item.h"

class Pickup : public Item
{
public:

	enum Type : int
	{
		kHeal,
		kAmmo,
		kScore,
		kKey
	};

	Pickup(glm::vec3 const& position, Type type, int t_id, int amount);
	void Update() override;
	void Render() override;

private:

	Type m_Type;
	int m_Amount;
	static const float s_PickupDistance;
	bool m_bIsEaten = false;
};