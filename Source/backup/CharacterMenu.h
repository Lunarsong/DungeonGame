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
	Character* m_pCharacter;
	UIElement* m_pMenu;

	// Character info
	UILabel* m_pLabelName;

	// Level & Experience
	UILabel* m_pLabelLevel;
	UILabel* m_pLabelExperience;

	// Stat Labels
	UILabel* m_pLabelCustomSTR;
	UILabel* m_pLabelCustomCON;
	UILabel* m_pLabelCustomDEX;
	UILabel* m_pLabelCustomINT;
	UILabel* m_pLabelCustomWILL;
	UILabel* m_pLabelCustomCHA;

	UILabel* m_pLabelPointsToSpend;

	// Stat buttons
	UIButton* m_ButtonSTR;
	UIButton* m_ButtonCON;
	UIButton* m_ButtonDEX;
	UIButton* m_ButtonINT;
	UIButton* m_ButtonWILL;
	UIButton* m_ButtonCHA;

	void BuyAbilityButton( UIElement* pElement, void* pArgs );
};

