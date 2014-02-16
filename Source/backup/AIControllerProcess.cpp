//
//  AIControllerProcess.cpp
//  DungeonGame
//
//  Created by Shanee on 1/7/14.
//
//

#include "AIControllerProcess.h"
#include "DungeonGame.h"
#include <Core/Application/BaseApplication.h>

AIControllerProcess::AIControllerProcess()
{
    
}

AIControllerProcess::~AIControllerProcess()
{
    
}

void AIControllerProcess::VOnInit()
{
	CharacterControllerProcess::VOnInit();

	float m_fTimer = 0.0f;
	m_eAIState = ActionIdle;
}

void AIControllerProcess::VOnSuccess()
{
    CharacterControllerProcess::VOnSuccess();
}

void AIControllerProcess::VOnFail()
{
    CharacterControllerProcess::VOnFail();
}

void AIControllerProcess::VOnAbort()
{
    CharacterControllerProcess::VOnAbort();
}

void AIControllerProcess::VOnUpdate( const float fDeltaSeconds )
{
	CharacterControllerProcess::VOnUpdate( fDeltaSeconds );
    
	const Vector3& vPosition = m_pCharacter->GetPosition();

	if ( IsProcessing() )
		return;

	switch ( m_eAIState )
	{
	case ActionIdle:
		{
			if ( IsActionAvailable( Attack ) && !m_pAttackableNodes.empty() )
			{
				PathfindingNode* pNode = NULL;
				float fDistance = FLT_MAX;
				for ( auto it : m_pAttackableNodes )
				{
					float fCurrentDistance = vPosition.DistanceSQ( it->GetPosition() );
					if ( fCurrentDistance < fDistance )
					{
						fDistance = fCurrentDistance;
						pNode = it;
					}
				}

				SelectNode( pNode );
			}

			else if ( IsActionAvailable( Walk ) )
			{
				bool bWander = true;
				// Get the game for enemies list
				DungeonGame* pGame = (DungeonGame*)BaseApplication::Get()->GetProcessManager().GetProcessByName( "Game" );
				if ( pGame )
				{
					float fDistance = FLT_MAX;
					CharacterComponent* pClosestPlayer = NULL;
					std::vector< CharacterComponent* > players = pGame->GetWorld().GetPlayers();

					for ( auto it : players )
					{
						float fCurrentDistance = it->GetPosition().DistanceSQ( m_pCharacter->GetPosition() );
						if ( fCurrentDistance < fDistance )
						{
							fDistance = fCurrentDistance;
							pClosestPlayer = it;
						}
					}

					if ( pClosestPlayer )
					{
						PathfindingNode* pClosestNode = NULL;
						fDistance = FLT_MAX;
						for ( auto it : m_pWalkableNodes )
						{
							float fCurrentDistance = it->GetPosition().DistanceSQ( pClosestPlayer->GetPosition() );
							if ( fCurrentDistance <= fDistance )
							{
								fDistance = fCurrentDistance;
								pClosestNode = it;
							}
						}

						if ( pClosestNode )
						{
							SelectNode( pClosestNode );
							bWander = false;
						}
					}

				}

				if ( bWander )
				{
					SelectNode( m_pWalkableNodes[ g_RandomNumGen.RandomInt( m_pWalkableNodes.size() ) ] );
				}

				
			}

		} break;

	case Process:
		{

		} break;

	default:
		break;
	}
}