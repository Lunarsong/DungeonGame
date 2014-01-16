//
//  AIControllerProcess.cpp
//  DungeonGame
//
//  Created by Shanee on 1/7/14.
//
//

#include "AIControllerProcess.h"

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
	m_eAIState = Idle;
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

	switch ( m_eAIState )
	{
	case Idle:
		{
			if ( !m_pAttackableNodes.empty() )
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

			else
			{
				SelectNode( m_pWalkableNodes[ g_RandomNumGen.RandomInt( m_pWalkableNodes.size() ) ] );
			}

			m_eAIState = Process;
		} break;

	case Process:
		{

		} break;

	default:
		break;
	}
}