#pragma once

#include "Equipment.h"

class Item
{
public:
	Item(void);
	virtual ~Item(void);

	Equipment::Slot EquipmentSlot;
	std::string Icon;

	enum ItemType
	{
		Weapon,
		Armor,

		Usable,

		Undefined
	};

	ItemType Type;

};

