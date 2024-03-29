#include "PotionItem.h"
#include "Character.h"

PotionItem::PotionItem(void)
{
	Icon = "potion.png";
}


PotionItem::~PotionItem(void)
{
}

void PotionItem::VOnUse( Character* pUsingCharacter )
{
	pUsingCharacter->GetAttribute( Health ).AdjustBase( 5 );
	pUsingCharacter->GetEquipment().GetInventory().RemoveItem( this );
}
