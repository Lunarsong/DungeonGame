//
//  AIController.h
//  DungeonGame
//
//  Created by Shanee on 1/6/14.
//
//

#include "World.h"

class AIController
{
public:
    AIController();
    ~AIController();
    
    void Update( World& world, float fDeltaSeconds );
    void TickleBrains( World& world, float fDeltaSeconds );
    
private:
    
};