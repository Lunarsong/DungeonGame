#pragma once

#include "Item.h"

class Armor : public Item
{
public:
	Armor(void);
	~Armor(void);

	int Rating;
};

