//
//  AIControllerProcess.h
//  DungeonGame
//
//  Created by Shanee on 1/7/14.
//
//

#pragma once

#include <Core/Process/Process.h>
#include "CharacterComponent.h"
#include "CharacterControllerProcess.h"

class AIControllerProcess : public CharacterControllerProcess
{
public:
    AIControllerProcess();
    ~AIControllerProcess();
    
    virtual void VOnInit();
    virtual void VOnSuccess();
    virtual void VOnFail();
    virtual void VOnAbort();
    
    virtual void VOnUpdate( const float fDeltaSeconds );    
    
private:    
    float m_fTimer;

	enum AIState
	{
		Idle,
		Process
	};
	AIState m_eAIState;
};