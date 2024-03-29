//
//  World.h
//  DungeonGame
//
//  Created by Shanee on 1/6/14.
//
//

#pragma once

#include <AI/Pathfinding/Graph/Implementations/SquarePathfindingGraph.h>

#include "GameMap.h"
#include "CharacterComponent.h"
#include <vector>

class World
{
public:
    World();
    ~World();
    
    void Init();
    
    void AddEnemy( CharacterComponent* pCharacter );
    void RemoveEnemy( CharacterComponent* pCharacter );
    
    void AddPlayer( CharacterComponent* pCharacter );
    void RemovePlayer( CharacterComponent* pCharacter );
    
    void AddEnemy( unsigned int iTileX, unsigned int iTileY );
    void CreatePlayer( unsigned int iTileX, unsigned iTileY );

    SquarePathfindingGraph* GetGraph();
    
    std::vector< CharacterComponent* >& GetEnemies();
    std::vector< CharacterComponent* >& GetPlayers();

	void SetCreateCharacterCallback( std::function< CharacterComponent*( const Vector3& ) > pCallback );
    
private:
    GameMap m_Map;
    SquarePathfindingGraph* m_PathGraph;
    
    std::vector< CharacterComponent* > m_pEnemies;
    std::vector< CharacterComponent* > m_pPlayers;
    
	std::list< Item* > m_pItems;

	std::function< CharacterComponent*( const Vector3& ) > m_pCreateCharacterCallback;
};