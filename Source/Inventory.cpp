#include "Inventory.h"


Inventory::Inventory(void)
{
	m_pItems.resize( 25 );
	for ( std::vector< Item* >::iterator pIter = m_pItems.begin(); pIter != m_pItems.end(); ++pIter )
	{
		*pIter = NULL;
	}
}


Inventory::~Inventory(void)
{
}

void Inventory::AddItem( Item* pItem )
{
	for ( auto it : m_pItems )
	{
		if ( it == pItem )
		{
			return;
		}
	}

	for ( std::vector< Item* >::iterator pIter = m_pItems.begin(); pIter != m_pItems.end(); ++pIter )
	{
		if ( *pIter == NULL )
		{
			*pIter = pItem;
			return;
		}
	}
}

void Inventory::RemoveItem( Item* pItem )
{
	for ( std::vector< Item* >::iterator pIter = m_pItems.begin(); pIter != m_pItems.end(); ++pIter )
	{
		if ( (*pIter) == pItem )
		{
			*pIter = NULL;
			break;
		}
	}
}
