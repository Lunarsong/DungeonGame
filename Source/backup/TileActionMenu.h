#pragma once

#include "Character.h"
#include <UI/UserInterface.h>

using namespace Engine;

class TileActionMenu
{
public:
	TileActionMenu(void);
	~TileActionMenu(void);

	void SetCharacter( Character* pCharacter );

	void Hide();
	void Show();

	void Update( float fDeltaSeconds );

private:
	Character* m_pCharacter;
	SmartPtr< UIElement > m_pElement;
};

