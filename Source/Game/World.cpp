#include "World.h"
#include <Core/Utils/Macros.h>
#include <Game/Entities/Components/Rendering/MeshComponent.h>
#include <Game/Game.h>
#include <Core/AssetManager/AssetManager.h>

using namespace Engine;

World::World( GameData* pGameData )
{
	assert( pGameData );
	m_pGameData = pGameData;
}

World::~World(void)
{
}

void World::Create( unsigned long ulSeed, unsigned int uiSize )
{
	m_uiSize = uiSize;

	m_TileMap.Create( uiSize, uiSize );

	VCreate( ulSeed, uiSize );
}

void World::AddSpawnPoint( int iX, int iY )
{
	m_SpawnPoints.push_back( Engine::Point( iX, iY ) );
}

Point World::GetSpawnPoint( int iIndex, bool bRemove /*= false */ )
{
	if ( bRemove )
	{
		Point p = m_SpawnPoints[ iIndex ];
		m_SpawnPoints.erase( m_SpawnPoints.begin() + iIndex );
		return p;
	}

	return m_SpawnPoints[ iIndex ];
}

Engine::Vector3 World::GetPositionForTile( int iX, int iY ) const
{
	return Vector3( -(int)m_uiSize * 0.5f + 0.5f + (float)iX, 0.0f, -(int)m_uiSize * 0.5f + 0.5f + (float)iY );
}

Point World::GetTilePosition( const Vector3& vPosition ) const
{
	Point pos;
	pos.x = vPosition.x - 0.5f + m_uiSize * 0.5f;
	pos.y = vPosition.z - 0.5f + m_uiSize * 0.5f;

	return pos;
}

void World::SetEntityPosition( Engine::Entity* pEntity, int iX, int iY )
{
	TilePositionComponent* pComponent = (TilePositionComponent*)pEntity->GetComponent( TilePositionComponent::GetComponentType() );
	if ( !pComponent )
	{
		pComponent = pEntity->AddComponent<TilePositionComponent>();
		pComponent->SetWorld( this );
	}

	pComponent->SetPosition( iX, iY );
}

Component& TilePositionComponent::operator=( const Component& other )
{
	const TilePositionComponent& castOther = (const TilePositionComponent&)other;

	m_pWorld = castOther.m_pWorld;
	m_Position = castOther.m_Position;

	return *this;
}
