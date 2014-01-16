#include "Equipment.h"
#include "Item.h"
#include <assert.h>
#include "Weapon.h"

Equipment::Equipment(void)
{
	for ( int i = 0; i < SlotCount; ++i )
	{
		m_pItems[ i ] = NULL;
	}

	m_pDefaultWeapon = new Weapon();
	m_pDefaultWeapon->Range = 1;
	m_pDefaultWeapon->Damage.Min = 2;
	m_pDefaultWeapon->Damage.Max = 6;
	m_pDefaultWeapon->EquipmentSlot = HandRight;
	m_pDefaultWeapon->Icon = "HandIcon.png";

	Equip( m_pDefaultWeapon );
}


Equipment::~Equipment(void)
{
	delete m_pDefaultWeapon;
}

Item* Equipment::GetItem( Slot eSlot )
{
	assert( eSlot < SlotCount );
	return m_pItems[ eSlot ];
}

Weapon* Equipment::GetWeapon()
{
	if ( m_pItems[ HandBoth ] )
	{
		return (Weapon*)m_pItems[ HandBoth ];
	}

	else if ( (Weapon*)m_pItems[ HandRight ] )
	{
		return (Weapon*)m_pItems[ HandRight ];
	}

	return NULL;
}

void Equipment::Equip( Item* pItem )
{
	if ( !pItem )
		return;

	m_Inventory.RemoveItem( pItem );

	if ( pItem->EquipmentSlot == HandBoth )
	{
		Unequip( HandBoth );
		Unequip( HandLeft );
		Unequip( HandRight );
	}

	else if ( pItem->EquipmentSlot == HandLeft )
	{
		Unequip( HandBoth );
		Unequip( HandLeft );
	}

	else if ( pItem->EquipmentSlot == HandRight )
	{
		Unequip( HandBoth );
		Unequip( HandRight );
	}

	m_pItems[ pItem->EquipmentSlot ] = pItem;
}

void Equipment::Unequip( Slot eSlot )
{
	Item* pItem = m_pItems[ eSlot ];
	m_pItems[ eSlot ] = NULL;

	if ( pItem && pItem != m_pDefaultWeapon )
	{
		m_Inventory.AddItem( pItem );
	}

	if ( ( eSlot == HandRight || eSlot == HandBoth ) && m_pItems[ HandRight ] == NULL )
	{
		m_pItems[ HandRight ] = m_pDefaultWeapon;
	}
}

Inventory& Equipment::GetInventory()
{
	return m_Inventory;
}
