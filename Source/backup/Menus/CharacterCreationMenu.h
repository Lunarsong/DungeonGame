#pragma once

#include <UI/UserInterface.h>
#include "../CharacterComponent.h"

using namespace Engine;

class CharacterCreationMenu
{
public:
	CharacterCreationMenu(void);
	~CharacterCreationMenu(void);

	void Init( Character* pCharacter );

	void ShowCustomCharacterCreation();

	bool IsCompleted() const;

private:
	bool m_bCompleted;
	UIElement* m_pCharacterCreationMenu;

	UILabel* m_pLabelCustomSTR;
	UILabel* m_pLabelCustomCON;
	UILabel* m_pLabelCustomDEX;
	UILabel* m_pLabelCustomINT;
	UILabel* m_pLabelCustomWILL;
	UILabel* m_pLabelCustomCHA;

	UILabel* m_pLabelStatPoints;

	Character* m_pCharacter;

	void UpdateStatFields();

	void ButtonSelectWarrior( UIElement* pElement, void* pArgs );
	void ButtonSelectArcher( UIElement* pElement, void* pArgs );
	void ButtonSelectMage( UIElement* pElement, void* pArgs );
	void ButtonSelectCustom( UIElement* pElement, void* pArgs );

	void ButtonSelectWeapon( UIElement* pElement, void* pArgs );
	enum WeaponSelected
	{
		None,
		Sword,
		Bow,
		Tome
	};
	WeaponSelected m_eWeaponSelected;

	void BuyAbilityButton( UIElement* pElement, void* pArgs );
	void ButtonCustomConfirm( UIElement* pElement, void* pArgs );

	void OnCompleteCharacterCreation();
};

