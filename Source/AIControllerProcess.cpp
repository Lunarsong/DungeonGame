//
//  AIControllerProcess.cpp
//  DungeonGame
//
//  Created by Shanee on 1/7/14.
//
//

#include "AIControllerProcess.h"

AIControllerProcess::AIControllerProcess()
{
    
}

AIControllerProcess::~AIControllerProcess()
{
    
}

void AIControllerProcess::VOnInit()
{
    m_fTimer = 5.0f;
}

void AIControllerProcess::VOnSuccess()
{
    
}

void AIControllerProcess::VOnFail()
{
    
}

void AIControllerProcess::VOnAbort()
{
    
}

void AIControllerProcess::VOnUpdate( const float fDeltaSeconds )
{
    m_fTimer -= fDeltaSeconds;
    
    if ( m_fTimer <= 0.0f )
    {
        Succeed();
    }
}

void AIControllerProcess::SetCharacter( CharacterComponent* pCharacter )
{
    m_pCharacter = pCharacter;
}