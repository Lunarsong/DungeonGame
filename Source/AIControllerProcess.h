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

class AIControllerProcess : public Engine::Process
{
public:
    AIControllerProcess();
    ~AIControllerProcess();
    
    virtual void VOnInit();
    virtual void VOnSuccess();
    virtual void VOnFail();
    virtual void VOnAbort();
    
    virtual void VOnUpdate( const float fDeltaSeconds );
    
    void SetCharacter( CharacterComponent* pCharacter );
    
private:
    Engine::SmartPtr<CharacterComponent> m_pCharacter;
    
    float m_fTimer;
};