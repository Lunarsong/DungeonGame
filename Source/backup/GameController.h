//
//  GameController.h
//  DungeonGame
//
//  Created by Shanee on 1/6/14.
//
//

#include "World.h"
#include "AIControllerProcess.h"
#include "PlayerControllerProcess.h"

class GameController
{
public:
    GameController();
    ~GameController();
    
    void Update( World& world, float fDeltaSeconds );

    void AddPlayer( CharacterComponent* pCharacter );
    void RemovePlayer( CharacterComponent* pCharacter );
    
    void AddAI( CharacterComponent* pCharacter );
    void RemoveAI( CharacterComponent* pCharacter );
    
private:
    enum State
    {
        Idle,
        UpdatingPlayers,
        UpdatingAI,
        
        StateCount
    };
    
    // Current state
    State m_eState;
    
    // List of active AI characters
    std::vector< SmartPtr<CharacterComponent> > m_pAICharacters;
    std::vector< SmartPtr<CharacterComponent> > m_pPlayerCharacters;
    unsigned int m_uiIteratorIndex;
    
    // Player & AI processes to keep track on
    AIControllerProcess* m_pAIProcess;
    PlayerControllerProcess* m_pPlayerProcess;
    
    void UpdatePlayers( World& world, float fDeltaSeconds );
    void UpdateAIs( World& world, float fDeltaSeconds );

	void AddAIs( World& world );
};