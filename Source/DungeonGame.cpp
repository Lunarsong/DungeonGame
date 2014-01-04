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

DungeonGame::DungeonGame()
{
    InputManager::Get()->AddMouseHandler( this );
}

DungeonGame::~DungeonGame()
{
    InputManager::Get()->RemoveMouseHandler( this );
    m_pCamera->Release();
    m_pCameraEntity->Release();
}

void DungeonGame::VOnInit(void)
{
    BinaryResource* pResource = AssetManager::Get().GetAsset< BinaryResource >( "Map.map" );
    
    m_Map.Create( pResource );
    
    ITexture* pMapTexture = AssetManager::Get().GetAsset< ITexture >( "Floor.png" );
    ITexture* pWallTexture = AssetManager::Get().GetAsset< ITexture >( "Wall.png" );
    ITexture* pChestTexture = AssetManager::Get().GetAsset< ITexture >( "Chest.png" );
    
    Material* pChestMaterial = new Material();
    pChestMaterial->AddTextureRegister( "s_Texture01" );
    pChestMaterial->SetShaderProgram( IRenderer::Get()->VGetShaderManager()->GetShaderProgram( PositionTextureNormal_DefaultShader ) );
    pChestMaterial->SetTexture( 0, pChestTexture );
    pChestTexture->Release();
    
    Material* pWallMaterial = new Material();
    pWallMaterial->AddTextureRegister( "s_Texture01" );
    pWallMaterial->SetShaderProgram( IRenderer::Get()->VGetShaderManager()->GetShaderProgram( PositionTextureNormal_DefaultShader ) );
    pWallMaterial->SetTexture( 0, pWallTexture );
    pWallTexture->Release();
    
    
    m_PathGraph.Create( m_Map.GetSizeX(), m_Map.GetSizeY(), 1.0f, false );
    Entity* pMapEntity = Game::CreateEntity();
    TileMapComponent* pTileMap = new TileMapComponent( m_Map.GetSizeX(), m_Map.GetSizeY(), 1.0f, pMapTexture, [&] ( unsigned int x, unsigned int y, RectF& rect )
                                                      {
                                                          float fX = -m_Map.GetSizeX() * 0.5f + 0.5f + (float)x;
                                                          float fY =  -m_Map.GetSizeY() * 0.5f + 0.5f + (float)y;

                                                          char myChar = m_Map( x, m_Map.GetSizeY() - 1 - y );
                                                          if ( myChar == '#' )
                                                          {
                                                              Entity* pCubeEntity = Game::CreateEntity();
                                                              
                                                              MeshComponent* pMesh = pCubeEntity->AddComponent<MeshComponent>();
                                                              pMesh->SetMesh( Mesh::CreateBox() );
                                                              pMesh->SetMaterial( pWallMaterial );
                                                              
                                                              pCubeEntity->GetTransform().SetPosition( Vector4( fX, 0.5f, fY ) );
                                                              
                                                              m_PathGraph.GetNode( x, y )->SetBlocked( true );
                                                          }
                                                          
                                                          else if ( myChar == 'C' )
                                                          {
                                                              Entity* pCubeEntity = Game::CreateEntity();
                                                              
                                                              MeshComponent* pMesh = pCubeEntity->AddComponent<MeshComponent>();
                                                              pMesh->SetMesh( Mesh::CreateBox() );
                                                              pMesh->SetMaterial( pChestMaterial );
                                                              
                                                              pCubeEntity->GetTransform().SetPosition( Vector4( fX, -0.49f, fY ) );
                                                              
                                                              m_PathGraph.GetNode( x, y )->SetBlocked( true );
                                                          }
                                                          
                                                          int iRand = g_RandomNumGen.RandomInt( 4 );
                                                          
                                                          rect.x = 0.25f * iRand;
                                                          rect.width = 0.25f + 0.25f * iRand;
                                                          
                                                          iRand = g_RandomNumGen.RandomInt( 4 );
                                                          rect.y = 0.25f * iRand;
                                                          rect.height = 0.25f + 0.25f * iRand;
                                                          
                                                          
                                                      }
                                                      );
    
    pWallMaterial->Release();
    pChestMaterial->Release();
    
    pMapEntity->AddComponent( pTileMap );
    pTileMap->Start();
    pTileMap->Release();
    
    ITexture* pCharacterTexture = AssetManager::Get().GetAsset< ITexture >( "Characters.png" );
    Material* pCharacterMaterial = new Material();
    pCharacterMaterial->AddTextureRegister( "s_Texture01" );
    pCharacterMaterial->SetShaderProgram( IRenderer::Get()->VGetShaderManager()->GetShaderProgram( PositionTextureNormal_DefaultShader ) );
    pCharacterMaterial->SetTexture( 0, pCharacterTexture );
    pCharacterTexture->Release();
    
    m_pPlayer = Game::CreateEntity();
    m_pPlayer->GetTransform().SetPosition( Vector4( 0.5f, 0.4f, 0.5f ) );
    MeshComponent* pMesh = m_pPlayer->AddComponent<MeshComponent>();
    
    RectF rect;
    rect.x = 805.0f / (float)pCharacterTexture->VGetWidth();
    rect.y = 365.0f / (float)pCharacterTexture->VGetHeight();

    rect.width = 895.0f / (float)pCharacterTexture->VGetWidth();
    rect.height = 445.0f / (float)pCharacterTexture->VGetHeight();
    
    pMesh->SetMesh( Mesh::CreateBox( Vector4::ONE * 0.8f, rect ) );
    pMesh->SetMaterial( pCharacterMaterial );
    pCharacterMaterial->Release();
    
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
    return true;
}

bool DungeonGame::VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition )
{
    return true;
}

bool DungeonGame::VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition )
{
    Vector3 vScreenPos = vPosition;
    vScreenPos.z = m_pCamera->GetPosition().y / 1000.0f;
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
    
    
    m_pPlayer->GetTransform().SetPosition( vGroundPosition );
    
    DebugRenderer::AddLine( vRayPos, vRayPos + vRayDir * 100.0f, ColorF::RED, 1.0f, 10.0f );
    DebugRenderer::AddLine( vRayPos, vRayPos + m_pCamera->GetDirection() * 100.0f, ColorF::BLUE, 1.0f, 10.0f );
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
