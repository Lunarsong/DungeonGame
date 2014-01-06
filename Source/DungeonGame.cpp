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

DungeonGame::DungeonGame()
{
    SetName( "Game" );
    InputManager::Get()->AddMouseHandler( this );
}

DungeonGame::~DungeonGame()
{
    InputManager::Get()->RemoveMouseHandler( this );
    m_pCamera->Release();
}

void DungeonGame::VOnInit(void)
{
    m_World.Init();
    
    // Load resources
    
    ITexture* pCharacterTexture = AssetManager::Get().GetAsset< ITexture >( "Characters.png" );
    // Create the material
    m_pCharactersMaterial = new StructuredMaterial<ColorF>();
    m_pCharactersMaterial->GetBuffer()->VAddProperty( "u_Color", BP_VECTOR4 );
    m_pCharactersMaterial->AddTextureRegister( "s_Texture01" );
    m_pCharactersMaterial->SetShaderProgram( IRenderer::Get()->VGetShaderManager()->GetShaderProgram( PositionTextureNormal_uColor_DefaultShader ) );
    m_pCharactersMaterial->GetData() = ColorF::WHITE;
    m_pCharactersMaterial->SetTexture( 0, pCharacterTexture );
    m_pCharactersMaterial->Release();
    
        
    // Create the player
    CreatePlayer();
    
    m_pCameraEntity = Game::CreateEntity();
    m_pCamera = new FreeCameraComponent();
    m_pCameraEntity->AddComponent( m_pCamera );
    m_pCameraEntity->GetTransform().SetPosition( Vector3( 0.0f, 5.0f, 0.0f ) );
    m_pCameraEntity->GetTransform().SetDirection( -Vector4::UP );

}

void DungeonGame::VOnUpdate( const float fDeltaSeconds )
{
    
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
    Vector3 vScreenPos = vPosition;
    Vector3 vRayPos, vRayDir;
    RenderUtils::Unproject( vScreenPos, m_pCamera->GetProjection(), m_pCamera->GetView(), vRayPos, vRayDir );
    vRayDir.Normalize();
    Plane groundPlane;
    groundPlane.InitFromPointNormal( Vector4::ZERO, Vector4::UP );
    
    Vector3 vGroundPosition;
    IntersectionUtils::RayPlaneIntersect( vRayPos, vRayPos + vRayDir * 1000.0f, groundPlane, vGroundPosition );
    
    DebugRenderer::AddLine( vRayPos, vRayPos + vRayDir * 1000.0f, ColorF::BLUE, 1.0f, 0.0f );
    
    return true;
}

bool DungeonGame::VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition )
{
    return true;
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
        pPickedEntity->OnMessage( "Interact", m_pPlayer, NULL );
        
    }
//    m_pPlayer->GetTransform().SetPosition( vGroundPosition );
    
    
    DebugRenderer::AddLine( vRayPos, vRayPos + vRayDir * 100.0f, ColorF::RED, 1.0f, 10.0f );
    
    return true;
}

bool DungeonGame::VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition )
{
    return true;
}

bool DungeonGame::VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta )
{
    return true;
}



void DungeonGame::CreatePlayer()
{
    m_pPlayer = Game::CreateEntity();
    m_pPlayer->GetTransform().SetPosition( Vector4( 0.5f, 0.4f, 0.5f ) );
    m_pPathFollower = m_pPlayer->AddComponent< PathFollowerComponent >();
    m_pPathFollower->SetGraph( m_World.GetGraph() );
    
    MeshComponent* pMesh = m_pPlayer->AddComponent<MeshComponent>();
    
    RectF rect;
    rect.x = 805.0f / (float)m_pCharactersMaterial->GetTexture( 0 )->VGetWidth();
    rect.y = 365.0f / (float)m_pCharactersMaterial->GetTexture( 0 )->VGetHeight();
    
    rect.width = 895.0f / (float)m_pCharactersMaterial->GetTexture( 0 )->VGetWidth();
    rect.height = 445.0f / (float)m_pCharactersMaterial->GetTexture( 0 )->VGetHeight();
    
    pMesh->SetMesh( Mesh::CreateBox( Vector4::ONE * 0.8f, rect ) );
	pMesh->GetMesh()->Release();
    pMesh->SetMaterial( m_pCharactersMaterial );
    
    CharacterComponent* pCharacter = m_pPlayer->AddComponent< CharacterComponent >();
    
}

World& DungeonGame::GetWorld()
{
    return m_World;
}