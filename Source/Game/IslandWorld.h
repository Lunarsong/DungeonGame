#pragma once

#include "world.h"
#include "IslandData.h"

class IslandWorld :
	public World
{
public:
	IslandWorld( GameData* pGameData );
	virtual ~IslandWorld(void);

	virtual void Create( unsigned long ulSeed, unsigned int uiSize );
	virtual Engine::IPathfindingGraph* GetPathGraph();

private:
	IslandData m_IslandData;
	Engine::IPathfindingGraph* m_pPathGraph;
};

