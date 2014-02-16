#include "Game.h"
#include "DungeonWorld.h"
#include <Rendering/Interfaces/ITexture.h>
#include <Rendering/Types/Material.h>
#include <Game/Game.h>
#include <Game/Entities/Components/Rendering/MeshComponent.h>

using namespace Engine;

Game::Game(void)
{
	m_pWorld = NULL;

	m_iCurrentFaction = 0;

	m_GameData.LoadFromFile( "GameData/Buildings.xml" );
}


Game::~Game(void)
{
	if ( m_pWorld )
	{
		delete m_pWorld;
		m_pWorld = NULL;
	}

	for ( auto it : m_Cities )
	{
		it->Release();
	}
}

void Game::Create( unsigned long ulSeed, unsigned int uiWorldSize )
{
	m_pWorld = new DungeonWorld( &m_GameData );
	m_pWorld->Create( ulSeed, uiWorldSize );

	CreatePlayers( 2 );
}

void Game::CreatePlayers( int iNumPlayers )
{
	m_Factions.resize( iNumPlayers );
	m_iCurrentFaction = 0;

	for ( int i = 0; i < iNumPlayers; ++i )
	{
		InitPlayer( m_Factions[ i ] );
	}
}

void Game::InitPlayer( Faction& pFaction )
{
	Point pos = m_pWorld->GetSpawnPoint( g_RandomNumGen.RandomInt( m_pWorld->GetNumSpawnPoints() ) );
	CreateCity( pos, pFaction );
	
}

City* Game::CreateCity( const Point& pos, Faction& owner )
{
	// Create a graphical entity
	ITexture* pTexture = AssetManager::Get().GetAsset< ITexture >( "BTNSteelMelee.png" );

	Material* pMaterial = new Material();
	pMaterial->AddTextureRegister( "s_Texture01" );
	pMaterial->SetShaderProgram( IRenderer::Get()->VGetShaderManager()->GetShaderProgram( PositionTextureNormal_DefaultShader ) );
	pMaterial->SetTexture( 0, pTexture );

	// Create entity
	Entity* pCubeEntity = GameManager::CreateEntity();

	MeshComponent* pMesh = pCubeEntity->AddComponent<MeshComponent>();
	pMesh->SetMesh( Mesh::CreateBox() );
	pMesh->GetMesh()->Release();
	pMesh->SetMaterial( pMaterial );

	pCubeEntity->GetTransform().SetPosition( m_pWorld->GetPositionForTile( pos.x, pos.y ) );

	pMaterial->Release();

	// Create the city
	City* pCity = pCubeEntity->AddComponent<City>();
	pCity->SetFaction( &owner );
	m_Cities.push_back( pCity );
	pCity->AddRef();

	m_pWorld->SetEntityPosition( pCubeEntity, pos.x, pos.y );

	return pCity;
}

void Game::EndTurn()
{
	OnTurnEnd( m_Factions[ m_iCurrentFaction ] );
	++m_iCurrentFaction;

	if ( m_iCurrentFaction >= m_Factions.size() )
	{
		m_iCurrentFaction = 0;
	}

	OnTurnStart( m_Factions[ m_iCurrentFaction ] );
}

void Game::OnTurnStart( Faction& faction )
{
	faction.OnTurnStart();
	VOnTurnStart( faction );
}

void Game::OnTurnEnd( Faction& faction )
{
	faction.OnTurnEnd();
	VOnTurnEnd( faction );
}

int Game::GetNumFactions() const
{
	return m_Factions.size();
}

Faction& Game::GetFaction( int iIndex )
{
	return m_Factions[ iIndex ];
}

void Game::Start()
{
	OnTurnStart( m_Factions[ m_iCurrentFaction ] );
}

void Game::End()
{

}

World& Game::GetWorld()
{
	return *m_pWorld;
}
