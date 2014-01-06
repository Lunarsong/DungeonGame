//
//  World.h
//  DungeonGame
//
//  Created by Shanee on 1/6/14.
//
//

#pragma once

#include <vector>
#include <AI/Pathfinding/Graph/Implementations/SquarePathfindingGraph.h>

#include "GameMap.h"
#include "CharacterComponent.h"

class World
{
public:
    World();
    ~World();
    
    void Init();
    
    void AddCharacter( CharacterComponent* pCharacter );
    void RemoveCharacter( CharacterComponent* pCharacter );
    
    void AddEnemy( const Vector3& vPosition );
    
    SquarePathfindingGraph* GetGraph();
    
    std::vector< CharacterComponent* >& GetCharacters();
    
private:
    GameMap m_Map;
    SquarePathfindingGraph* m_PathGraph;
    
    std::vector< CharacterComponent* > m_pCharacters;
    
};