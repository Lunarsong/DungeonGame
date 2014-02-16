#include "IslandWorld.h"
#include <Core/Utils/Macros.h>

IslandWorld::IslandWorld( GameData* pGameData ) : World( pGameData )
{
	m_pPathGraph = NULL;
}


IslandWorld::~IslandWorld(void)
{
	SAFE_RELEASE( m_pPathGraph );
}

void IslandWorld::Create( unsigned long ulSeed, unsigned int uiSize )
{

}

Engine::IPathfindingGraph* IslandWorld::GetPathGraph()
{
	return m_pPathGraph;
}
