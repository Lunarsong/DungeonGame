#include "CharacterMenu.h"
#include <Engine.h>
#include "Weapon.h"

using namespace Engine;
CharacterMenu::CharacterMenu(void)
{
	m_pCharacter = NULL;

	m_pMenu		= Engine::UserInterface::AddScreenFromFile( "CharacterMenu", "CharacterMenu.xml" );
	m_pMenu->SetVisible( false, true );

	// Stats
	m_pLabelCustomSTR = (UILabel*)m_pMenu->GetElement( "lbl_str" );
	m_pLabelCustomCON = (UILabel*)m_pMenu->GetElement( "lbl_con" );
	m_pLabelCustomDEX = (UILabel*)m_pMenu->GetElement( "lbl_dex" );
	m_pLabelCustomINT = (UILabel*)m_pMenu->GetElement( "lbl_int" );
	m_pLabelCustomWILL = (UILabel*)m_pMenu->GetElement( "lbl_will" );
	m_pLabelCustomCHA = (UILabel*)m_pMenu->GetElement( "lbl_cha" );

	// Buttons
	m_ButtonSTR = (UIButton*)m_pMenu->GetElement( "btn_str" );
	m_ButtonCON = (UIButton*)m_pMenu->GetElement( "btn_con" );
	m_ButtonDEX = (UIButton*)m_pMenu->GetElement( "btn_dex" );
	m_ButtonINT = (UIButton*)m_pMenu->GetElement( "btn_int" );
	m_ButtonWILL = (UIButton*)m_pMenu->GetElement( "btn_will" );
	m_ButtonCHA = (UIButton*)m_pMenu->GetElement( "btn_cha" );

	//
	m_pLabelName = (UILabel*)m_pMenu->GetElement( "lbl_name" );

	// Level & Experience
	m_pLabelLevel = (UILabel*)m_pMenu->GetElement( "lbl_level" );
	m_pLabelExperience = (UILabel*)m_pMenu->GetElement( "lbl_experience" );
	m_pLabelPointsToSpend = (UILabel*)m_pMenu->GetElement( "lbl_stat_points" );

	{
		auto pCallback = std::bind( &CharacterMenu::BuyAbilityButton, this, std::placeholders::_1, std::placeholders::_2 );
		m_ButtonSTR->SetCallbackArgs( (void*)Strength );
		m_ButtonSTR->SetCallbackFunction( pCallback );

		m_ButtonCON->SetCallbackArgs( (void*)Constitution );
		m_ButtonCON->SetCallbackFunction( pCallback );

		m_ButtonDEX->SetCallbackArgs( (void*)Dexterity );
		m_ButtonDEX->SetCallbackFunction( pCallback );

		m_ButtonINT->SetCallbackArgs( (void*)Intelligence );
		m_ButtonINT->SetCallbackFunction( pCallback );

		m_ButtonWILL->SetCallbackArgs( (void*)Willpower );
		m_ButtonWILL->SetCallbackFunction( pCallback );

		m_ButtonCHA->SetCallbackArgs( (void*)Charisma );
		m_ButtonCHA->SetCallbackFunction( pCallback );
	}

	//m_pLabelStatPoints = (UILabel*)m_pCharacterCreationMenu->GetElement( "lbl_stat_points" );

	/*((Engine::UIButton*)m_pMenu->GetElement( "btn_resume" ))->SetCallbackFunction( [ this ] ( Engine::UIElement* pElement, void* pData )
	{
		Hide();
	}
	);


	((Engine::UIButton*)m_pMenu->GetElement( "btn_options" ))->SetCallbackFunction( [ this ] ( Engine::UIElement* pElement, void* pData )
	{
		Hide();
	}
	);


	((Engine::UIButton*)m_pMenu->GetElement( "btn_exit" ))->SetCallbackFunction( [ this ] ( Engine::UIElement* pElement, void* pData )
	{
		Engine::BaseApplication::Get()->VQuit();
	}
	);*/
}


CharacterMenu::~CharacterMenu(void)
{
	Engine::UserInterface::RemoveScreen( m_pMenu );
}

void CharacterMenu::Show()
{
	m_pMenu->SetVisible( true, true );
}

void CharacterMenu::Hide()
{
	m_pMenu->SetVisible( false, true );
}

void CharacterMenu::ToggleVisibility()
{
	m_pMenu->SetVisible( !m_pMenu->IsVisible(), true );
}

void CharacterMenu::Update( Character* pCharacter )
{
	m_pCharacter = pCharacter;

	if ( m_pMenu->IsVisible() )
	{
		m_pLabelCustomSTR->SetString( ToString( pCharacter->GetAttribute( Strength ).GetValue() ) );
		m_pLabelCustomCON->SetString( ToString( pCharacter->GetAttribute( Constitution ).GetValue() ) );
		m_pLabelCustomDEX->SetString( ToString( pCharacter->GetAttribute( Dexterity ).GetValue() ) );
		m_pLabelCustomINT->SetString( ToString( pCharacter->GetAttribute( Intelligence ).GetValue() ) );
		m_pLabelCustomWILL->SetString( ToString( pCharacter->GetAttribute( Willpower ).GetValue() ) );
		m_pLabelCustomCHA->SetString( ToString( pCharacter->GetAttribute( Charisma ).GetValue() ) );

		int iLevel = pCharacter->GetLevel();
		m_pLabelName->SetString( "[NAME]" );
		m_pLabelLevel->SetString( "Level " + ToString( iLevel ) );
		m_pLabelExperience->SetString( "Experience " + ToString( pCharacter->GetExperience() ) + "/" + ToString( Character::CalculateExperienceForLevel( iLevel + 1 ) ) );

		int iAttributePoints = pCharacter->GetAttributePoints();
		if ( iAttributePoints > 0 )
		{
			m_pLabelPointsToSpend->SetVisible( true );
			m_pLabelPointsToSpend->SetString( "To Spend: " + ToString( iAttributePoints ) );

			m_ButtonSTR->SetEnabled( true );
			m_ButtonCON->SetEnabled( true );
			m_ButtonDEX->SetEnabled( true );
			m_ButtonINT->SetEnabled( true );
			m_ButtonWILL->SetEnabled( true );
			m_ButtonCHA->SetEnabled( true );
		}

		else
		{
			m_pLabelPointsToSpend->SetVisible( false );

			m_ButtonSTR->SetEnabled( false );
			m_ButtonCON->SetEnabled( false );
			m_ButtonDEX->SetEnabled( false );
			m_ButtonINT->SetEnabled( false );
			m_ButtonWILL->SetEnabled( false );
			m_ButtonCHA->SetEnabled( false );
		}
	}

	/*UIImage* pImage = (UIImage*)m_pMenu->GetElement( "img_hand");
	if ( pImage )
	{
		Item* pItem = pCharacter->GetEquipment().GetWeapon();
		if ( pItem )
		{
			pImage->SetTexture( pItem->Icon );
		}

		else
		{
			pImage->SetTexture( "HandIcon.png" );
		}
	}*/
	
}

void CharacterMenu::BuyAbilityButton( UIElement* pElement, void* pArgs )
{
	if ( m_pCharacter )
	{
		m_pCharacter->BuyAttribute( (Attributes)(int)pArgs );
	}
}