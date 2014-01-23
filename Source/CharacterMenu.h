#pragma once

#include <UI/UserInterface.h>
#include "Character.h"

using namespace Engine;
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
	UIElement* m_pMenu;

	// Character info
	UILabel* m_pLabelName;

	// Level & Experience
	UILabel* m_pLabelLevel;
	UILabel* m_pLabelExperience;

	// Stats
	UILabel* m_pLabelCustomSTR;
	UILabel* m_pLabelCustomCON;
	UILabel* m_pLabelCustomDEX;
	UILabel* m_pLabelCustomINT;
	UILabel* m_pLabelCustomWILL;
	UILabel* m_pLabelCustomCHA;
};

