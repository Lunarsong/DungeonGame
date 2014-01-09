//
//  PlayerControllerProcess.cpp
//  DungeonGame
//
//  Created by Shanee on 1/7/14.
//
//

#include "PlayerControllerProcess.h"
#include <Rendering/Utils/RenderUtils.h>
#include <Rendering/Scene/SceneManager.h>
#include <Game/Entities/Components/Rendering/RenderComponent.h>
#include <Game/Entities/Entity.h>
#include <Engine.h>

PlayerControllerProcess::PlayerControllerProcess()
{
    
}

PlayerControllerProcess::~PlayerControllerProcess()
{
    
}

void PlayerControllerProcess::VOnInit()
{
    m_ePlayerState = AwaitingInput;
    
    InputManager::Get()->AddMouseHandler( this );
}

void PlayerControllerProcess::VOnSuccess()
{
    InputManager::Get()->RemoveMouseHandler( this );
}

void PlayerControllerProcess::VOnFail()
{
    InputManager::Get()->RemoveMouseHandler( this );
}

void PlayerControllerProcess::VOnAbort()
{
    InputManager::Get()->RemoveMouseHandler( this );
}

void PlayerControllerProcess::VOnUpdate( const float fDeltaSeconds )
{
    if ( m_ePlayerState == Processing )
    {
        if ( m_pPathFollower->IsFollowingPath() == false )
        {
            m_ePlayerState = Done;
        }
    }
    
    if ( m_ePlayerState == Done )
    {
        Succeed();
    }
}

void PlayerControllerProcess::SetCharacter( CharacterComponent* pCharacter )
{
    m_pCharacter = pCharacter;
    m_pPathFollower = m_pCharacter->GetOwner()->GetComponent< PathFollowerComponent >();
}

bool PlayerControllerProcess::VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition )
{
    return false;
}

bool PlayerControllerProcess::VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition )
{
    return false;
}

bool PlayerControllerProcess::VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition )
{
    if ( m_ePlayerState != AwaitingInput )
        return false;
    
    const Camera* pCamera = SceneManager::Get()->GetActiveCamera();
    
    Vector3 vScreenPos = vPosition;
    Vector3 vRayPos, vRayDir;
    RenderUtils::Unproject( vScreenPos, pCamera->GetProjection(), pCamera->GetView(), vRayPos, vRayDir );
    vRayDir.Normalize();
    Plane groundPlane;
    groundPlane.InitFromPointNormal( Vector4::ZERO, Vector4::UP );
    
    Vector3 vGroundPosition;
    IntersectionUtils::RayPlaneIntersect( vRayPos, vRayPos + vRayDir * 1000.0f, groundPlane, vGroundPosition );
    m_pPathFollower->SetDestination( vGroundPosition );
    //vGroundPosition.x = (int)(vGroundPosition.x - 0.25f) + 0.5f;
    if ( vGroundPosition.x < 0.0f )
    {
        vGroundPosition.x = (int)(vGroundPosition.x) - 0.5f;
    }
    else
    {
        vGroundPosition.x = (int)(vGroundPosition.x) + 0.5f;
    }
    
    if ( vGroundPosition.z < 0.0f )
    {
        vGroundPosition.z = (int)(vGroundPosition.z) - 0.5f;
    }
    else
    {
        vGroundPosition.z = (int)(vGroundPosition.z) + 0.5f;
    }
    
    SceneNode* pSceneNode = SceneManager::Get()->VPickAndReturnClosest( vRayPos, vRayDir );
    RenderComponent* pNode = dynamic_cast< RenderComponent* >( pSceneNode );
    if ( pNode )
    {
        pNode = pNode;
        Entity* pPickedEntity = pNode->GetOwner();
        pPickedEntity->OnMessage( "Interact", m_pCharacter->GetOwner(), NULL );
        
    }
    //    m_pPlayer->GetTransform().SetPosition( vGroundPosition );
    
    m_ePlayerState = Processing;
    
    return true;
}

bool PlayerControllerProcess::VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition )
{
    return false;
}

bool PlayerControllerProcess::VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta )
{
    return false;
}


