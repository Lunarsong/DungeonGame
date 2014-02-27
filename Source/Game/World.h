#pragma once

#include <AI/Pathfinding/Graph/BasePathfindingGraph.h>
#include "TileMap.h"
#include "GameData.h"
#include <Core/Math/Point.h>

using Engine::Point;

class World
{
public:
	World( GameData* pGameData );
	virtual ~World(void);

	void Create( unsigned long ulSeed, unsigned int uiSize );
	virtual Engine::IPathfindingGraph* GetPathGraph()=0;

	void AddSpawnPoint( int iX, int iY );
	int GetNumSpawnPoints() const { return m_SpawnPoints.size(); }
	Point GetSpawnPoint( int iIndex, bool bRemove = false );

	TileMap& GetTileMap() { return m_TileMap; }
	const TileMap& GetTileMap() const { return m_TileMap; }

	GameData* GetGameData() { return m_pGameData; }
	const GameData* GetGameData() const { return m_pGameData; }

	Vector3 GetPositionForTile( int iX, int iY ) const;
	Point GetTilePosition( const Vector3& vPosition ) const;

	void SetEntityPosition( Engine::Entity*, int iX, int iY );

protected:
	unsigned int m_uiSize;

	GameData* m_pGameData;
	TileMap m_TileMap;

	virtual void VCreate( unsigned long ulSeed, unsigned int uiSize )=0;

	std::vector< Engine::Point > m_SpawnPoints;
};

class TilePositionComponent : public Engine::Component
{
public:
	TilePositionComponent() { }
	~TilePositionComponent() { }

	SET_TYPE( "TilePositionComponent" );

	const Point& GetPointPosition() const
	{
		return m_Position;
	}

	void SetPosition( int iX, int iY )
	{
		m_pWorld->GetTileMap()( m_Position.x, m_Position.y ).RemoveEntity( m_pOwner );

		m_Position.x = iX;
		m_Position.y = iY;

		m_pWorld->GetTileMap()( m_Position.x, m_Position.y ).AddEntity( m_pOwner );
	}

	void SetWorld( World* pWorld ) { m_pWorld = pWorld; }

	virtual Component& operator=( const Component& other );

private:
	World* m_pWorld;
	Point m_Position;
};
