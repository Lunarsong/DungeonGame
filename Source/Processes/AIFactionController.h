#pragma once
#include "factioncontroller.h"
class AIFactionController :
	public FactionController
{
public:
	AIFactionController( Game* pGame );
	virtual ~AIFactionController(void);

	virtual void VOnInit(void);
	virtual void VOnUpdate( const float fDeltaSeconds );
	virtual void VOnSuccess(void);
	virtual void VOnAbort(void);
};

