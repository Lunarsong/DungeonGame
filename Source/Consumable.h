#pragma once

#include "Item.h"


class Character;

class Consumable : public Item
{
public:
	Consumable(void);
	virtual ~Consumable(void);

	virtual void VOnUse( Character* pUsingCharacter ) { }
};

