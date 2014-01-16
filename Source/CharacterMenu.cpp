#include "CharacterMenu.h"
#include <Engine.h>
#include "Weapon.h"

using namespace Engine;
CharacterMenu::CharacterMenu(void)
{
	m_pMenu		= Engine::UserInterface::AddScreenFromFile( "CharacterMenu", "CharacterMenu.xml" );
	m_pMenu->SetVisible( false, true );

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
	UIImage* pImage = (UIImage*)m_pMenu->GetElement( "img_hand");
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
	}

}
