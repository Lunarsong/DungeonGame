//
//  DungeonGame.h
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#pragma once

#include <Core/Process/Process.h>
#include <AI/Pathfinding/Graph/Implementations/SquarePathfindingGraph.h>
#include <Core/Input/InputHandlers.h>
#include <Game/Game.h>
#include <Game/Entities/Components/Rendering/CameraComponent.h>
#include "GameMap.h"

using namespace Engine;

class DungeonGame : public Engine::Process, public IMouseHandler
{
public:
    DungeonGame();
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
    
private:
    GameMap m_Map;
    SquarePathfindingGraph m_PathGraph;
    
    Entity* m_pPlayer;
    Entity* m_pCameraEntity;
    CameraComponent* m_pCamera;
};