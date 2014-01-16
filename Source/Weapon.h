#pragma once

#include "Item.h"

class Weapon : public Item
{
public:
	Weapon(void);
	~Weapon(void);

	int Range;
	struct DamageRange
	{
		int Min;
		int Max;
	};
	DamageRange Damage;

};

