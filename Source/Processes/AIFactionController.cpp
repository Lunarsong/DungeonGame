#include "AIFactionController.h"


AIFactionController::AIFactionController( Game* pGame ) : FactionController( pGame )
{
}


AIFactionController::~AIFactionController(void)
{
}

void AIFactionController::VOnInit( void )
{
	FactionController::VOnInit();
}

void AIFactionController::VOnUpdate( const float fDeltaSeconds )
{
	FactionController::VOnUpdate( fDeltaSeconds );

	EndTurn();
}

void AIFactionController::VOnSuccess( void )
{
	FactionController::VOnSuccess();
}

void AIFactionController::VOnAbort( void )
{
	FactionController::VOnAbort();
}
