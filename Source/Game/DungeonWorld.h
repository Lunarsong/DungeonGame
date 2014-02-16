#pragma once

#include "world.h"
#include "CaveGeneator.h"
#include <AI/Pathfinding/Graph/Implementations/SquarePathfindingGraph.h>


class DungeonWorld :
	public World
{
public:
	DungeonWorld( GameData* pGameData );
	virtual ~DungeonWorld(void);

	virtual void VCreate( unsigned long ulSeed, unsigned int uiSize );
	virtual Engine::IPathfindingGraph* GetPathGraph();

private:
	Engine::SquarePathfindingGraph* m_pPathGraph;

	CaveGeneator m_Cave;

	void CreateSpawnPoints( int iNumSpawnPoints );
	bool CreateSpawnPoint( const std::pair< int, int >& offset, const int iSearchSize, int& x, int& y );
};

