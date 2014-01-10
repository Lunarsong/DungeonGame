//
//  GameController.cpp
//  DungeonGame
//
//  Created by Shanee on 1/6/14.
//
//

#include "GameController.h"
#include <Engine.h>

GameController::GameController()
{
    m_pAICharacters.reserve( 40 );
    m_pPlayerCharacters.reserve( 6 );
    
    m_eState = Idle;
    m_uiIteratorIndex = 0;
    
    // Create the AI & player process and abort it
    m_pAIProcess = new AIControllerProcess();
    m_pAIProcess->Abort();
    
    m_pPlayerProcess = new PlayerControllerProcess();
    m_pPlayerProcess->Abort();
}

GameController::~GameController()
{
    SAFE_RELEASE( m_pPlayerProcess );
    SAFE_RELEASE( m_pAIProcess );
}

void GameController::Update( World& world, float fDeltaSeconds )
{
    switch ( m_eState )
    {
        case Idle:
            m_uiIteratorIndex = 0;
            m_eState = UpdatingPlayers;
            //break;
            
        case UpdatingPlayers:
            UpdatePlayers( world, fDeltaSeconds );
            break;
            
        case UpdatingAI:
            UpdateAIs( world, fDeltaSeconds );
            break;
            
        default:
            break;
    }
}

void GameController::UpdatePlayers( World& world, float fDeltaSeconds )
{
    if ( m_pPlayerProcess->IsDead() )
    {
        ++m_uiIteratorIndex;
        
        if ( m_uiIteratorIndex > m_pPlayerCharacters.size() )
        {
            m_eState = UpdatingAI;
            m_uiIteratorIndex = 0;
            
            return;
        }
        
        // Set the current process and activate it
        m_pPlayerProcess->SetCharacter( m_pPlayerCharacters[ m_uiIteratorIndex-1 ] );
        BaseApplication::Get()->AttachProcess( m_pPlayerProcess );
    }
}

void GameController::UpdateAIs( World& world, float fDeltaSeconds )
{
    if ( m_pAIProcess->IsDead() )
    {
        ++m_uiIteratorIndex;
        
        if ( m_uiIteratorIndex > m_pAICharacters.size() )
        {
            m_eState = UpdatingPlayers;
            m_uiIteratorIndex = 0;
            
            return;
        }
        
        // Set the current process and activate it
        m_pAIProcess->SetCharacter( m_pAICharacters[ m_uiIteratorIndex-1 ] );
        BaseApplication::Get()->AttachProcess( m_pAIProcess );
    }
}

void GameController::AddAI( CharacterComponent* pCharacter )
{
    m_pAICharacters.push_back( pCharacter );
}

void GameController::RemoveAI( CharacterComponent* pCharacter )
{
    std::vector< SmartPtr< CharacterComponent > >::iterator pIter;
    for ( pIter = m_pAICharacters.begin(); pIter != m_pAICharacters.end(); ++pIter )
    {
        SmartPtr< CharacterComponent > pIterCharacter = *pIter;
        if ( pCharacter == pIterCharacter )
        {
            m_pAICharacters.erase( pIter );
            return;
        }
    }
}

void GameController::AddPlayer( CharacterComponent* pCharacter )
{
    m_pPlayerCharacters.push_back( pCharacter );
}

void GameController::RemovePlayer( CharacterComponent* pCharacter )
{
    std::vector< SmartPtr< CharacterComponent > >::iterator pIter;
    for ( pIter = m_pPlayerCharacters.begin(); pIter != m_pPlayerCharacters.end(); ++pIter )
    {
        SmartPtr< CharacterComponent > pIterCharacter = *pIter;
        if ( pCharacter == pIterCharacter )
        {
            m_pPlayerCharacters.erase( pIter );
            return;
        }
    }
}