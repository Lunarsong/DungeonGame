#include "CharacterCreationMenu.h"
#include <string>
#include <Core/Logging/Log.h>


CharacterCreationMenu::CharacterCreationMenu(void)
{
	m_pCharacter = NULL;
	m_eWeaponSelected = None;
	m_bCompleted = false;
}


CharacterCreationMenu::~CharacterCreationMenu(void)
{
	UserInterface::RemoveScreen( m_pCharacterCreationMenu );
}

void CharacterCreationMenu::ShowCustomCharacterCreation()
{
	m_pCharacterCreationMenu->GetElement( "menu_path" )->SetVisible( false, true );
	m_pCharacterCreationMenu->GetElement( "menu_custom" )->SetVisible( true, true );

	UpdateStatFields();
}

void CharacterCreationMenu::Init( Character* pCharacter )
{
	m_pCharacter = pCharacter;
	m_eWeaponSelected = None;

	m_pCharacterCreationMenu = UserInterface::AddScreenFromFile( "CharacterCreation", "CharacterCreation.xml" );

	m_pLabelCustomSTR = (UILabel*)m_pCharacterCreationMenu->GetElement( "lbl_str" );
	m_pLabelCustomCON = (UILabel*)m_pCharacterCreationMenu->GetElement( "lbl_con" );
	m_pLabelCustomDEX = (UILabel*)m_pCharacterCreationMenu->GetElement( "lbl_dex" );
	m_pLabelCustomINT = (UILabel*)m_pCharacterCreationMenu->GetElement( "lbl_int" );
	m_pLabelCustomWILL = (UILabel*)m_pCharacterCreationMenu->GetElement( "lbl_will" );
	m_pLabelCustomCHA = (UILabel*)m_pCharacterCreationMenu->GetElement( "lbl_cha" );

	m_pLabelStatPoints = (UILabel*)m_pCharacterCreationMenu->GetElement( "lbl_stat_points" );


	// Attribute callbacks
	{
		auto pCallback = std::bind( &CharacterCreationMenu::BuyAbilityButton, this, std::placeholders::_1, std::placeholders::_2 );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_str" ))->SetCallbackArgs( (void*)Strength );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_str" ))->SetCallbackFunction( pCallback );

		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_con" ))->SetCallbackArgs( (void*)Constitution );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_con" ))->SetCallbackFunction( pCallback );

		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_dex" ))->SetCallbackArgs( (void*)Dexterity );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_dex" ))->SetCallbackFunction( pCallback );

		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_int" ))->SetCallbackArgs( (void*)Intelligence );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_int" ))->SetCallbackFunction( pCallback );

		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_will" ))->SetCallbackArgs( (void*)Willpower );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_will" ))->SetCallbackFunction( pCallback );

		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_cha" ))->SetCallbackArgs( (void*)Charisma );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_cha" ))->SetCallbackFunction( pCallback );
	}

	// Confirm callback
	{
		auto pCallback = std::bind( &CharacterCreationMenu::ButtonCustomConfirm, this, std::placeholders::_1, std::placeholders::_2 );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_confirm" ))->SetCallbackFunction( pCallback );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_confirm" ))->SetEnabled( false );
	}
	

	// Weapon callback
	{
		auto pCallback = std::bind( &CharacterCreationMenu::ButtonSelectWeapon, this, std::placeholders::_1, std::placeholders::_2 );	
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_sword" ))->SetCallbackArgs( (void*)Sword );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_sword" ))->SetCallbackFunction( pCallback );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_bow" ))->SetCallbackArgs( (void*)Bow );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_bow" ))->SetCallbackFunction( pCallback );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_tome" ))->SetCallbackArgs( (void*)Tome );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_tome" ))->SetCallbackFunction( pCallback );
	}

	// Class callbacks
	{
		auto pCallback = std::bind( &CharacterCreationMenu::ButtonSelectWarrior, this, std::placeholders::_1, std::placeholders::_2 );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_warrior" ))->SetCallbackFunction( pCallback );
	}

	{
		auto pCallback = std::bind( &CharacterCreationMenu::ButtonSelectArcher, this, std::placeholders::_1, std::placeholders::_2 );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_archer" ))->SetCallbackFunction( pCallback );
	}

	{
		auto pCallback = std::bind( &CharacterCreationMenu::ButtonSelectMage, this, std::placeholders::_1, std::placeholders::_2 );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_mage" ))->SetCallbackFunction( pCallback );
	}

	{
		auto pCallback = std::bind( &CharacterCreationMenu::ButtonSelectCustom, this, std::placeholders::_1, std::placeholders::_2 );
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_custom" ))->SetCallbackFunction( pCallback );
	}

	//ButtonSelectWarrior( NULL, NULL );
}

void CharacterCreationMenu::UpdateStatFields()
{
	m_pLabelCustomSTR->SetString( ToString( m_pCharacter->GetAttribute( Strength ).GetValue() ) );
	m_pLabelCustomCON->SetString( ToString( m_pCharacter->GetAttribute( Constitution ).GetValue() ) );
	m_pLabelCustomDEX->SetString( ToString( m_pCharacter->GetAttribute( Dexterity ).GetValue() ) );
	m_pLabelCustomINT->SetString( ToString( m_pCharacter->GetAttribute( Intelligence ).GetValue() ) );
	m_pLabelCustomWILL->SetString( ToString( m_pCharacter->GetAttribute( Willpower ).GetValue() ) );
	m_pLabelCustomCHA->SetString( ToString( m_pCharacter->GetAttribute( Charisma ).GetValue() ) );

	int iAttributePoints = m_pCharacter->GetAttributePoints();
	m_pLabelStatPoints->SetString( "To Spend: " + ToString( iAttributePoints ) );

	if ( iAttributePoints == 0 && m_eWeaponSelected != None )
	{
		((UIButtonImage*)m_pCharacterCreationMenu->GetElement( "btn_confirm" ))->SetEnabled( true );
	}
}

void CharacterCreationMenu::BuyAbilityButton( UIElement* pElement, void* pArgs )
{
	m_pCharacter->BuyAttribute( (Attributes)(int)pArgs );
	UpdateStatFields();
}

void CharacterCreationMenu::ButtonSelectWarrior( UIElement* pElement, void* pArgs )
{
	m_pCharacter->BuyAttribute( Strength );
	m_pCharacter->BuyAttribute( Strength );
	m_pCharacter->BuyAttribute( Strength );
	m_pCharacter->BuyAttribute( Constitution );
	m_pCharacter->BuyAttribute( Constitution );

	m_eWeaponSelected = Sword;

	OnCompleteCharacterCreation();
}

void CharacterCreationMenu::ButtonSelectArcher( UIElement* pElement, void* pArgs )
{
	m_pCharacter->BuyAttribute( Strength );
	m_pCharacter->BuyAttribute( Strength );
	m_pCharacter->BuyAttribute( Constitution );
	m_pCharacter->BuyAttribute( Dexterity );
	m_pCharacter->BuyAttribute( Dexterity );

	m_eWeaponSelected = Bow;

	OnCompleteCharacterCreation();
}

void CharacterCreationMenu::ButtonSelectMage( UIElement* pElement, void* pArgs )
{
	m_pCharacter->BuyAttribute( Willpower );
	m_pCharacter->BuyAttribute( Willpower );
	m_pCharacter->BuyAttribute( Intelligence );
	m_pCharacter->BuyAttribute( Intelligence );
	m_pCharacter->BuyAttribute( Constitution );

	m_eWeaponSelected = Tome;

	OnCompleteCharacterCreation();
}

void CharacterCreationMenu::ButtonSelectCustom( UIElement* pElement, void* pArgs )
{
	ShowCustomCharacterCreation();
}

void CharacterCreationMenu::ButtonCustomConfirm( UIElement* pElement, void* pArgs )
{
	OnCompleteCharacterCreation();
}

void CharacterCreationMenu::ButtonSelectWeapon( UIElement* pElement, void* pArgs )
{
	m_eWeaponSelected = (WeaponSelected)(int)pArgs;

	UpdateStatFields();
}

void CharacterCreationMenu::OnCompleteCharacterCreation()
{
	m_bCompleted = true;
}

bool CharacterCreationMenu::IsCompleted() const
{
	return m_bCompleted;
}
