//
//  PlayerControllerProcess.h
//  DungeonGame
//
//  Created by Shanee on 1/7/14.
//
//

#pragma once

#include <Core/Process/Process.h>
#include <Core/Input/InputHandlers.h>
#include <Game/Entities/Components/AI/PathFollowerComponent.h>

#include "CharacterComponent.h"

using namespace Engine;

class PlayerControllerProcess : public Process, public IMouseHandler
{
public:
    PlayerControllerProcess();
    ~PlayerControllerProcess();
    
    virtual void VOnInit();
    virtual void VOnSuccess();
    virtual void VOnFail();
    virtual void VOnAbort();
    
    virtual void VOnUpdate( const float fDeltaSeconds );
    
    void SetCharacter( CharacterComponent* pCharacter );
    
    // Mouse handling
    virtual bool VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition );
    virtual bool VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta );
    
private:
    SmartPtr<CharacterComponent> m_pCharacter;
    SmartPtr<PathFollowerComponent> m_pPathFollower;
    float m_fTimer;
    
    enum PlayerState
    {
        AwaitingInput,
        Processing,
        Done
    };
    
    PlayerState m_ePlayerState;
};