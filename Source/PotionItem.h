#pragma once

#include "Consumable.h"

class PotionItem : public Consumable
{
public:
	PotionItem(void);
	~PotionItem(void);

	virtual void VOnUse( Character* pUsingCharacter );
};

