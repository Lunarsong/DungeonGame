#pragma once

#include <Core/Process/Process.h>
#include "../Game/Faction/Faction.h"
#include "../Game/Game.h"

class FactionController : public Engine::Process
{
public:
	FactionController( Game* pGame );
	virtual ~FactionController(void);

	virtual void VOnInit(void);
	virtual void VOnUpdate( const float fDeltaSeconds );
	virtual void VOnSuccess(void);
	virtual void VOnAbort(void);

	void SetFaction( Faction* pFaction );

	Game* GetGame();
	void EndTurn();

private:
	Game* m_pGame;
	Faction* m_pFaction;
};

