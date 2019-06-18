#pragma once

#include "Item.h"

class Pickup : public Item
{
public:

	enum Type : int
	{
		kHeal,
		kAmmo,
		kScore
	};

	Pickup(glm::vec3 const& position, Type type, int t_id, int amount);
	void Update() override;
	void Render() override;

private:

	int m_Type;
	int m_Amount;
	bool m_bIsEaten = false;
	static constexpr float s_PickupDistance = 1.0f;
};