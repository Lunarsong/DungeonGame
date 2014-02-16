#include "MainMenuProcess.h"
#include <Engine.h>
#include "GameProcess.h"

MainMenuProcess::MainMenuProcess(void)
{
}


MainMenuProcess::~MainMenuProcess(void)
{

}

void MainMenuProcess::VOnInit( void )
{
	UIElement* pScreen = UserInterface::AddScreenFromFile( "MainMenu", "Screens/MainMenu.xml" );
	pScreen->GetElement<UIButton>( "btn_new_game" )->SetCallbackFunction( [&] ( UIElement* pElement, void* pArgs )
	{
		GameProcess* pGameProcess = new GameProcess();
		AttachChild( pGameProcess );
		pGameProcess->Release();

		Succeed();
	});
}

void MainMenuProcess::VOnUpdate( const float fDeltaSeconds )
{

}

void MainMenuProcess::VOnSuccess( void )
{
	UserInterface::RemoveScreen( "MainMenu" );
}

void MainMenuProcess::VOnFail( void )
{

}

void MainMenuProcess::VOnAbort( void )
{

}
