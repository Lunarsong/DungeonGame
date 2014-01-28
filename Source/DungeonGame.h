//
//  DungeonGame.h
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#pragma once

#include <Core/Process/Process.h>
#include <Core/Input/InputHandlers.h>
#include <Game/Game.h>
#include <Game/Entities/Components/Rendering/CameraComponent.h>
#include <Game/Entities/Components/AI/PathFollowerComponent.h>
#include "World.h"
#include "GameController.h"
#include <Core/EventManager/IEventManager.h>

using namespace Engine;

class DungeonGame : public Engine::Process, public IMouseHandler
{
public:
    DungeonGame( CharacterComponent* pCharacter = NULL );
    ~DungeonGame();
    
    virtual void VOnInit(void);
    virtual void VOnUpdate( const float fDeltaSeconds );
    virtual void VOnSuccess(void);
    virtual void VOnFail(void);
    virtual void VOnAbort(void);
    
    // Mouse handling
    virtual bool VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition );
    virtual bool VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta );
    
    World& GetWorld();

	CameraComponent* GetCamera();
    
private:
    World m_World;
    GameController m_GameController;
    
    PathFollowerComponent* m_pPathFollower;
    Entity* m_pCameraEntity;
    CameraComponent* m_pCamera;  

	SmartPtr<CharacterComponent> m_pPlayerCharacter;

	void OnCharacterDied( Engine::Event pEvent );
};