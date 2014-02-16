#include "DungeonWorld.h"
#include <Core/Utils/Macros.h>
#include <Engine.h>
#include <Game/Entities/Components/Rendering/TileMapComponent.h>
#include <Game/Entities/Components/Rendering/MeshComponent.h>

using namespace Engine;

DungeonWorld::DungeonWorld( GameData* pGameData ) : World( pGameData )
{
	m_pPathGraph = NULL;
}


DungeonWorld::~DungeonWorld(void)
{
	SAFE_RELEASE( m_pPathGraph );
}

void DungeonWorld::VCreate( unsigned long ulSeed, unsigned int uiSize )
{
	// Prepare A* Grid
	m_pPathGraph = new Engine::SquarePathfindingGraph();
	m_pPathGraph->Create( uiSize, uiSize, 1.0f, false );

	m_Cave.Generate( ulSeed, uiSize, uiSize, 10, 40 );

	ITexture* pMapTexture = AssetManager::Get().GetAsset< ITexture >( "Floor.png" );
	ITexture* pWallTexture = AssetManager::Get().GetAsset< ITexture >( "Wall.png" );

	Material* pWallMaterial = new Material();
	pWallMaterial->AddTextureRegister( "s_Texture01" );
	pWallMaterial->SetShaderProgram( IRenderer::Get()->VGetShaderManager()->GetShaderProgram( PositionTextureNormal_DefaultShader ) );
	pWallMaterial->SetTexture( 0, pWallTexture );

	Entity* pMapEntity = GameManager::CreateEntity();
	TileMapComponent* pTileMap = new TileMapComponent( uiSize, uiSize, 1.0f, pMapTexture, [&] ( unsigned int x, unsigned int y, RectF& rect )
	{
		float fX = -(int)uiSize * 0.5f + 0.5f + (float)x;
		float fY =  -(int)uiSize * 0.5f + 0.5f + (float)y;

		int myChar = m_Cave( x, y );
		if ( myChar == TILE_WALL )
		{
			Entity* pCubeEntity = GameManager::CreateEntity();

			MeshComponent* pMesh = pCubeEntity->AddComponent<MeshComponent>();
			pMesh->SetMesh( Mesh::CreateBox() );
			pMesh->GetMesh()->Release();
			pMesh->SetMaterial( pWallMaterial );

			pCubeEntity->GetTransform().SetPosition( Vector4( fX, 0.5f, fY ) );

			m_pPathGraph->GetNode( x, y )->SetBlocked( true );
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

	pMapEntity->AddComponent( pTileMap );
	pTileMap->Release();


	// Create players spawn points
	CreateSpawnPoints( 2 );
}

Engine::IPathfindingGraph* DungeonWorld::GetPathGraph()
{
	return m_pPathGraph;
}

void DungeonWorld::CreateSpawnPoints( int iNumSpawnPoints )
{
	int iSearchSize = m_uiSize / 3;

	std::vector< std::pair< int, int > > offsets;
	offsets.push_back( std::make_pair( 2, 2 ) );
	offsets.push_back( std::make_pair( m_uiSize - iSearchSize - 2, 2 ) );
	offsets.push_back( std::make_pair( 2, m_uiSize - iSearchSize - 2 ) );
	offsets.push_back( std::make_pair( m_uiSize - iSearchSize - 2, m_uiSize - iSearchSize - 2 ) );
	for ( int i = 0; i < iNumSpawnPoints; ++i )
	{
		int x;
		int y;

		while ( true )
		{
			int iRandom = g_RandomNumGen.RandomInt( offsets.size() );
			if ( CreateSpawnPoint( offsets[ iRandom ], iSearchSize, x, y ) )
			{
				offsets.erase( offsets.begin() + iRandom );
				break;
			}
		}

		AddSpawnPoint( x, y );
	}
}

bool DungeonWorld::CreateSpawnPoint( const std::pair< int, int >& offset, const int iSearchSize, int& x, int& y )
{
	x = offset.first + g_RandomNumGen.RandomInt( iSearchSize );
	y = offset.second + g_RandomNumGen.RandomInt( iSearchSize );

	if ( m_Cave( x, y ) == TILE_FLOOR )
	{
		for ( int i = -2; i <= 2; ++i )
		{
			for ( int j = -2; j <= 2; ++j )
			{
				if ( m_Cave( x + i, y + j ) != TILE_FLOOR )
					return false;
			}
		}

		return true;
	}

	return false;
}
