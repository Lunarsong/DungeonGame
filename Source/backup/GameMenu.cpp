#include "GameMenu.h"
#include <Engine.h>

GameMenu::GameMenu(void)
{
	m_pMenu		= Engine::UserInterface::AddScreenFromFile( "GameMenu", "GameMenu.xml" );
	m_pMenu->SetVisible( false, true );

	((Engine::UIButton*)m_pMenu->GetElement( "btn_resume" ))->SetCallbackFunction( [ this ] ( Engine::UIElement* pElement, void* pData )
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
	);
}


GameMenu::~GameMenu(void)
{
	Engine::UserInterface::RemoveScreen( m_pMenu );
}

void GameMenu::Show()
{
	m_pMenu->SetVisible( true, true );
}

void GameMenu::Hide()
{
	m_pMenu->SetVisible( false, true );
}
