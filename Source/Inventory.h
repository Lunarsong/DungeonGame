#pragma once

#include <vector>
#include <cstring>
class Item;

class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	void AddItem( Item* pItem );
	void RemoveItem( Item* pItem );

	size_t Size() { return m_pItems.size(); }

	const std::vector< Item* >& GetItems() { return m_pItems; }
private:
	std::vector< Item* > m_pItems;
};

