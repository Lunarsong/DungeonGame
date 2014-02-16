#include "FactionController.h"


FactionController::FactionController( Game* pGame )
{
	m_pGame = pGame;
	m_pFaction = NULL;
}

FactionController::~FactionController(void)
{
}

void FactionController::VOnInit( void )
{

}

void FactionController::VOnUpdate( const float fDeltaSeconds )
{

}

void FactionController::VOnSuccess( void )
{

}

void FactionController::VOnAbort( void )
{

}

void FactionController::SetFaction( Faction* pFaction )
{
	m_pFaction = pFaction;
}

Game* FactionController::GetGame()
{
	return m_pGame;
}

void FactionController::EndTurn()
{
	m_pGame->EndTurn();
}
