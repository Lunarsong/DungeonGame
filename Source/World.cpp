//
//  World.cpp
//  DungeonGame
//
//  Created by Shanee on 1/6/14.
//
//

#include "World.h"

#include <Engine.h>
#include <Game/Entities/Components/Rendering/TileMapComponent.h>
#include <Game/Entities/Components/Rendering/MeshComponent.h>
#include <Game/Entities/Components/AI/PathFollowerComponent.h>
#include "Weapon.h"
#include "PotionItem.h"

using namespace Engine;

World::World()
{
    m_PathGraph = NULL;
}

World::~World()
{
    SAFE_RELEASE( m_PathGraph );

	for ( auto it : m_pItems )
	{
		delete it;
	}
}

void World::Init()
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
    
    Material* pWallMaterial = new Material();
    pWallMaterial->AddTextureRegister( "s_Texture01" );
    pWallMaterial->SetShaderProgram( IRenderer::Get()->VGetShaderManager()->GetShaderProgram( PositionTextureNormal_DefaultShader ) );
    pWallMaterial->SetTexture( 0, pWallTexture );
    
    
    // Create the map
    m_PathGraph = new SquarePathfindingGraph();
    m_PathGraph->SetTolerance( 0.01f );
    m_PathGraph->Create( m_Map.GetSizeX(), m_Map.GetSizeY(), 1.0f, false );
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
															  pMesh->GetMesh()->Release();
                                                              pMesh->SetMaterial( pWallMaterial );
                                                              
                                                              pCubeEntity->GetTransform().SetPosition( Vector4( fX, 0.5f, fY ) );
                                                              
                                                              m_PathGraph->GetNode( x, y )->SetBlocked( true );
                                                          }
                                                          
                                                          else if ( myChar == 'C' )
                                                          {
                                                              Entity* pCubeEntity = Game::CreateEntity();
                                                              
                                                              MeshComponent* pMesh = pCubeEntity->AddComponent<MeshComponent>();
                                                              pMesh->SetMesh( Mesh::CreateBox() );
															  pMesh->GetMesh()->Release();
                                                              pMesh->SetMaterial( pChestMaterial );
                                                              
                                                              pCubeEntity->GetTransform().SetPosition( Vector4( fX, -0.49f, fY ) );
                                                              
                                                              m_PathGraph->GetNode( x, y )->SetBlocked( true );
															  m_PathGraph->GetNode( x, y )->SetData( (void*)pCubeEntity );
                                                          }
                                                          
                                                          else if ( myChar == 'E' )
                                                          {
                                                              AddEnemy( x, y );
                                                              //m_PathGraph->GetNode( x, y )->SetBlocked( true );
                                                          }

														  else if ( myChar == 'P' )
														  {
															  CreatePlayer( x, y );
															  //m_PathGraph->GetNode( x, y )->SetBlocked( true );
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
    pTileMap->Release();
}

void World::AddEnemy( CharacterComponent* pCharacter )
{
	pCharacter->SetAI( true );
    m_pEnemies.push_back( pCharacter );
}

void World::RemoveEnemy( CharacterComponent* pCharacter )
{
    for ( std::vector<CharacterComponent*>::iterator pIter = m_pEnemies.begin(); pIter != m_pEnemies.end(); ++pIter )
    {
        if ( (*pIter) == pCharacter )
        {
            m_pEnemies.erase( pIter );
            return;
        }
    }
}

void World::AddPlayer( CharacterComponent* pCharacter )
{
	pCharacter->SetAI( false );
    m_pPlayers.push_back( pCharacter );
}

void World::RemovePlayer( CharacterComponent* pCharacter )
{
    for ( std::vector<CharacterComponent*>::iterator pIter = m_pPlayers.begin(); pIter != m_pPlayers.end(); ++pIter )
    {
        if ( (*pIter) == pCharacter )
        {
            m_pPlayers.erase( pIter );
            return;
        }
    }
}

void World::AddEnemy( unsigned int iTileX, unsigned int iTileY )
{
	float fX = -m_Map.GetSizeX() * 0.5f + 0.5f + (float)iTileX;
	float fY =  -m_Map.GetSizeY() * 0.5f + 0.5f + (float)iTileY;
	Vector3 vPosition( fX, 0.0f, fY );

	ITexture* pCharacterTexture = AssetManager::Get().GetAsset< ITexture >( "Characters.png" );
	Entity* pEntity = Game::CreateEntity();

	MeshComponent* pMesh = pEntity->AddComponent<MeshComponent>();
	RectF rect;
	rect.x = 6.0f / (float)pCharacterTexture->VGetWidth();
	rect.y = 6.0f / (float)pCharacterTexture->VGetHeight();

	rect.width = 95.0f / (float)pCharacterTexture->VGetWidth();
	rect.height = 85.0f / (float)pCharacterTexture->VGetHeight();

	pMesh->SetMesh( Mesh::CreateBox( Vector4::ONE * 0.8f, rect ) );
	pMesh->GetMesh()->Release();

	// Create the material
	StructuredMaterial<ColorF>* pMaterial = new StructuredMaterial<ColorF>();
	pMaterial->GetBuffer()->VAddProperty( "u_Color", BP_VECTOR4 );
	pMaterial->AddTextureRegister( "s_Texture01" );
	pMaterial->SetShaderProgram( IRenderer::Get()->VGetShaderManager()->GetShaderProgram( PositionTextureNormal_uColor_DefaultShader ) );
	pMaterial->GetData() = ColorF::WHITE;
	pMaterial->SetTexture( 0, pCharacterTexture );

	// Set the material
	pMesh->SetMaterial( pMaterial );
	pMaterial->Release();

	CharacterComponent* pCharacter = pEntity->AddComponent< CharacterComponent >();
	PathFollowerComponent* pFollowerComponent = pEntity->AddComponent< PathFollowerComponent >();
	pFollowerComponent->SetGraph( m_PathGraph );

	pEntity->GetTransform().SetPosition( vPosition );

	m_PathGraph->GetNode( iTileX, iTileY )->SetData( (void*)pEntity );
	m_PathGraph->GetNode( iTileX, iTileY )->SetBlocked( true );

	AddEnemy( pCharacter );
}

void World::CreatePlayer( unsigned int iTileX, unsigned iTileY )
{
	float fX = -m_Map.GetSizeX() * 0.5f + 0.5f + (float)iTileX;
	float fY =  -m_Map.GetSizeY() * 0.5f + 0.5f + (float)iTileY;
	Vector3 vPosition( fX, 0.0f, fY );

	Entity* pPlayer = Game::CreateEntity();
	pPlayer->GetTransform().SetPosition( vPosition );
	PathFollowerComponent* pPathFollower = pPlayer->AddComponent< PathFollowerComponent >();
	pPathFollower->SetGraph( GetGraph() );

	MeshComponent* pMesh = pPlayer->AddComponent<MeshComponent>();

	ITexture* pCharacterTexture = AssetManager::Get().GetAsset< ITexture >( "Characters.png" );

	RectF rect;
	rect.x = 805.0f / (float)pCharacterTexture->VGetWidth();
	rect.y = 365.0f / (float)pCharacterTexture->VGetHeight();

	rect.width = 895.0f / (float)pCharacterTexture->VGetWidth();
	rect.height = 445.0f / (float)pCharacterTexture->VGetHeight();

	// Create the material
	StructuredMaterial<ColorF>* pCharactersMaterial = new StructuredMaterial<ColorF>();
	pCharactersMaterial->GetBuffer()->VAddProperty( "u_Color", BP_VECTOR4 );
	pCharactersMaterial->AddTextureRegister( "s_Texture01" );
	pCharactersMaterial->SetShaderProgram( IRenderer::Get()->VGetShaderManager()->GetShaderProgram( PositionTextureNormal_uColor_DefaultShader ) );
	pCharactersMaterial->GetData() = ColorF::WHITE;
	pCharactersMaterial->SetTexture( 0, pCharacterTexture );


	pMesh->SetMesh( Mesh::CreateBox( Vector4::ONE * 0.8f, rect ) );
	pMesh->GetMesh()->Release();
	pMesh->SetMaterial( pCharactersMaterial );
	pCharactersMaterial->Release();

	CharacterComponent* pCharacter = pPlayer->AddComponent< CharacterComponent >();
	AddPlayer( pCharacter );

	m_PathGraph->GetNode( iTileX, iTileY )->SetData( (void*)pPlayer );
	m_PathGraph->GetNode( iTileX, iTileY )->SetBlocked( true );

	Weapon* pSword = new Weapon();
	pSword->Icon = "AbilitySwords.png";
	m_pItems.push_back( pSword );
	pCharacter->GetEquipment().GetInventory().AddItem( pSword );

	Weapon* pBow = new Weapon();
	pBow->Range = 6;
	pBow->Icon = "AbilityBow.png";
	m_pItems.push_back( pBow );
	pCharacter->GetEquipment().GetInventory().AddItem( pBow );

	PotionItem* pPotion = new PotionItem();
	m_pItems.push_back( pPotion );
	pCharacter->GetEquipment().GetInventory().AddItem( pPotion );

	pPotion = new PotionItem();
	m_pItems.push_back( pPotion );
	pCharacter->GetEquipment().GetInventory().AddItem( pPotion );

	pPotion = new PotionItem();
	m_pItems.push_back( pPotion );
	pCharacter->GetEquipment().GetInventory().AddItem( pPotion );

	pPotion = new PotionItem();
	m_pItems.push_back( pPotion );
	pCharacter->GetEquipment().GetInventory().AddItem( pPotion );

	pPotion = new PotionItem();
	m_pItems.push_back( pPotion );
	pCharacter->GetEquipment().GetInventory().AddItem( pPotion );

	pPotion = new PotionItem();
	m_pItems.push_back( pPotion );
	pCharacter->GetEquipment().GetInventory().AddItem( pPotion );

	

}

SquarePathfindingGraph* World::GetGraph()
{
	return m_PathGraph;
}

std::vector< CharacterComponent* >& World::GetEnemies()
{
	return m_pEnemies;
}

std::vector< CharacterComponent* >& World::GetPlayers()
{
	return m_pPlayers;
}