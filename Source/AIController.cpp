//
//  AIController.cpp
//  DungeonGame
//
//  Created by Shanee on 1/6/14.
//
//

#include "AIController.h"

AIController::AIController()
{
    
}

AIController::~AIController()
{
    
}

void AIController::Update( World& world, float fDeltaSeconds )
{
    
}

void AIController::TickleBrains( World& world, float fDeltaSeconds )
{
    std::vector< CharacterComponent* >& arrCharacters = world.GetCharacters();
    for ( auto pCharacter : arrCharacters )
    {
        
    }
}