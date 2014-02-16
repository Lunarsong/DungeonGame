#pragma once

#include <UI/UserInterface.h>
#include "Inventory.h"
#include "Character.h"

class InventoryMenu
{
public:
	InventoryMenu(void);
	~InventoryMenu(void);

	void Show();
	void Hide();
	void ToggleVisibility();

	void UpdateContents( Inventory& inventory );
	void SetCharacter( Character* pCharacter );

private:
	Engine::UIElement* m_pMenu;
	Character* m_pCharacter;
};

