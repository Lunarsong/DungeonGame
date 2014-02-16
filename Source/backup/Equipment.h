#pragma once
#include "Inventory.h"

class Item;
class Weapon;

class Equipment
{
public:
	Equipment(void);
	~Equipment(void);

	enum Slot
	{
		Head = 0,
		Chest,
		Ring,
		Pendant,
		HandLeft,
		HandRight,
		HandBoth,

		None,
		SlotCount = None
	};

	Item* GetItem( Slot eSlot );
	Weapon* GetWeapon();
	void Equip( Item* pItem );
	void Unequip( Slot eSlot );

	Inventory& GetInventory();

private:
	Item* m_pItems[ SlotCount ];
	Inventory m_Inventory;

	Weapon* m_pDefaultWeapon;
};

#include "Item.h"
