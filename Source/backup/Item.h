#pragma once

#include "Equipment.h"
#include <string>
#include "GameEntity.h"

class Item : public GameEntity
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

