#include "CharacterMenu.h"
#include <Engine.h>
#include "Weapon.h"

using namespace Engine;
CharacterMenu::CharacterMenu(void)
{
	m_pMenu		= Engine::UserInterface::AddScreenFromFile( "CharacterMenu", "CharacterMenu.xml" );
	m_pMenu->SetVisible( false, true );

	// Stats
	m_pLabelCustomSTR = (UILabel*)m_pMenu->GetElement( "lbl_str" );
	m_pLabelCustomCON = (UILabel*)m_pMenu->GetElement( "lbl_con" );
	m_pLabelCustomDEX = (UILabel*)m_pMenu->GetElement( "lbl_dex" );
	m_pLabelCustomINT = (UILabel*)m_pMenu->GetElement( "lbl_int" );
	m_pLabelCustomWILL = (UILabel*)m_pMenu->GetElement( "lbl_will" );
	m_pLabelCustomCHA = (UILabel*)m_pMenu->GetElement( "lbl_cha" );

	//
	m_pLabelName = (UILabel*)m_pMenu->GetElement( "lbl_name" );

	// Level & Experience
	m_pLabelLevel = (UILabel*)m_pMenu->GetElement( "lbl_level" );
	m_pLabelExperience = (UILabel*)m_pMenu->GetElement( "lbl_experience" );

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
