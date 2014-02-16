#include "MainMenuProcess.h"
#include "..\DungeonGame.h"
#include <Engine.h>

MainMenuProcess::MainMenuProcess(void)
{
}


MainMenuProcess::~MainMenuProcess(void)
{
	m_pCharacter->Release();
}

void MainMenuProcess::VOnInit( void )
{
	m_pCharacter = new CharacterComponent();
	m_pCharacter->AdjustAttributePoints( 5 );
	m_CharacterCreation.Init( m_pCharacter );
}

void MainMenuProcess::VOnUpdate( const float fDeltaSeconds )
{
	if ( m_CharacterCreation.IsCompleted() )
	{
		DungeonGame* pDungeonGame = new DungeonGame( (CharacterComponent*)m_pCharacter );
		AttachChild( pDungeonGame );
		pDungeonGame->Release();

		Succeed();

		Log << "MainMenu Done!";
	}
}

void MainMenuProcess::VOnSuccess( void )
{

}

void MainMenuProcess::VOnFail( void )
{

}

void MainMenuProcess::VOnAbort( void )
{

}
