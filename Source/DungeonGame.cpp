//
//  DungeonGame.cpp
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#include "DungeonGame.h"
#include <Game/Entities/Components/Rendering/TileMapComponent.h>
#include <Game/Entities/Components/Rendering/MeshComponent.h>
#include <Game/Entities/Components/Rendering/FreeCameraComponent.h>
#include <Engine.h>
#include <Rendering/Utils/RenderUtils.h>
#include <Rendering/Utils/DebugRenderer.h>
#include "CharacterComponent.h"
#include "CharacterEvents.h"

DungeonGame::DungeonGame()
{
	m_pCamera = NULL;

    SetName( "Game" );
    InputManager::Get()->AddMouseHandler( this );

	EventManager::AddListener( "EventCharacterDied", MakeDelegate( this, &DungeonGame::OnCharacterDied ) );
}

DungeonGame::~DungeonGame()
{
	EventManager::RemoveListener( "EventCharacterDied", MakeDelegate( this, &DungeonGame::OnCharacterDied ) );

    InputManager::Get()->RemoveMouseHandler( this );
    m_pCamera->Release();
}

void DungeonGame::VOnInit(void)
{
    m_World.Init();

	auto players = m_World.GetPlayers();
	for ( auto it : players )
	{
		m_GameController.AddPlayer( it );
	}


	auto enemies = m_World.GetEnemies();
	for ( auto it : enemies )
	{
		m_GameController.AddAI( it );
	}
           
    m_pCameraEntity = Game::CreateEntity();
    m_pCamera = new FreeCameraComponent();
    m_pCameraEntity->AddComponent( m_pCamera );
    m_pCameraEntity->GetTransform().SetPosition( Vector3( 0.0f, 5.0f, 0.0f ) );
    m_pCameraEntity->GetTransform().SetDirection( -Vector4::UP );
}

void DungeonGame::VOnUpdate( const float fDeltaSeconds )
{
    m_GameController.Update( m_World, fDeltaSeconds );
}

void DungeonGame::VOnSuccess(void)
{
    
}

void DungeonGame::VOnFail(void)
{
    
}

void DungeonGame::VOnAbort(void)
{
    
}

bool DungeonGame::VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition )
{
	if ( !m_pCamera )
		return false;

    Vector3 vScreenPos = vPosition;
    Vector3 vRayPos, vRayDir;
    RenderUtils::Unproject( vScreenPos, m_pCamera->GetProjection(), m_pCamera->GetView(), vRayPos, vRayDir );
    vRayDir.Normalize();
    Plane groundPlane;
    groundPlane.InitFromPointNormal( Vector4::ZERO, Vector4::UP );
    
    Vector3 vGroundPosition;
    IntersectionUtils::RayPlaneIntersect( vRayPos, vRayPos + vRayDir * 1000.0f, groundPlane, vGroundPosition );
    
    //DebugRenderer::AddLine( vRayPos, vRayPos + vRayDir * 1000.0f, ColorF::BLUE, 1.0f, 0.0f );
    
    return false;
}

bool DungeonGame::VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition )
{
    return false;
}

bool DungeonGame::VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition )
{
    Vector3 vScreenPos = vPosition;
    Vector3 vRayPos, vRayDir;
    RenderUtils::Unproject( vScreenPos, m_pCamera->GetProjection(), m_pCamera->GetView(), vRayPos, vRayDir );
    vRayDir.Normalize();
    Plane groundPlane;
    groundPlane.InitFromPointNormal( Vector4::ZERO, Vector4::UP );
    
    Vector3 vGroundPosition;
    IntersectionUtils::RayPlaneIntersect( vRayPos, vRayPos + vRayDir * 1000.0f, groundPlane, vGroundPosition );

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
        //pPickedEntity->OnMessage( "Interact", m_pPlayer, NULL );
        
    }
    
    return false;
}

bool DungeonGame::VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition )
{
    return false;
}

bool DungeonGame::VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta )
{
    return false;
}

World& DungeonGame::GetWorld()
{
    return m_World;
}

void DungeonGame::OnCharacterDied( Event pEvent )
{
	EventCharacterDied* pEventData = (EventCharacterDied*)pEvent.get();
	CharacterComponent* pCharacter = (CharacterComponent*)pEventData->GetCharacter();
	
	m_World.RemoveEnemy( pCharacter );
	m_GameController.RemoveAI( pCharacter );

	m_World.RemovePlayer( pCharacter );
	m_GameController.RemovePlayer( pCharacter );

	PathfindingNode* pPathNode = m_World.GetGraph()->VFindClosestNode( pCharacter->GetPosition() );
	pPathNode->SetData( NULL );
	pPathNode->SetBlocked( false );

	Game::DestroyEntity( pCharacter->GetOwner() );
}
