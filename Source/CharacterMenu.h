#pragma once

#include <UI/UserInterface.h>
#include "Character.h"

class CharacterMenu
{
public:
	CharacterMenu(void);
	~CharacterMenu(void);

	void Show();
	void Hide();

	void ToggleVisibility();

	void Update( Character* pCharacter );

private:
	Engine::UIElement* m_pMenu;
};

