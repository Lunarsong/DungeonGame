#include "CharacterControllerProcess.h"
#include <Rendering/Utils/RenderUtils.h>
#include <Rendering/Scene/SceneManager.h>
#include <Game/Entities/Components/Rendering/RenderComponent.h>
#include <Game/Entities/Entity.h>
#include <Engine.h>
#include <Rendering/Scene/SceneManager.h>
#include <Game/Entities/Components/Rendering/CameraComponent.h>
#include <Engine.h>
#include "DungeonGame.h"
#include <Rendering/Utils/DebugRenderer.h>
#include <algorithm>
#include "Weapon.h"

CharacterControllerProcess::CharacterControllerProcess(void)
{
}


CharacterControllerProcess::~CharacterControllerProcess(void)
{
}



void CharacterControllerProcess::GetLegalWalkTiles()
{
	m_pWalkableNodes.clear();

	if ( IsActionAvailable( Walk ) == false )
		return;

	float fSpeed = (float)m_pCharacter->GetAttribute( Speed ).GetValue();
	Vector3 vPosition = m_pCharacter->GetTransform().GetPosition();

	m_pPathGraph->VFindAllNodesWithinCost( m_pPathGraph->VFindClosestNode( vPosition ), fSpeed, m_pWalkableNodes );
}

void CharacterControllerProcess::VOnInit()
{
	AddAction( Attack );
	AddAction( Walk );
	m_pEntityToAttack = NULL;
	m_eState = ActionIdle;
}

void CharacterControllerProcess::VOnSuccess()
{
	PathfindingNode* pCurrentNode = m_pPathGraph->VFindClosestNode( m_pCharacter->GetPosition() );
	if ( pCurrentNode )
	{
		pCurrentNode->SetBlocked( true );
		pCurrentNode->SetData( m_pCharacter->GetOwner() );
	}
}

void CharacterControllerProcess::VOnFail()
{
}

void CharacterControllerProcess::VOnAbort()
{

}

void CharacterControllerProcess::VOnUpdate( const float fDeltaSeconds )
{
	// Get the current weapon for the entity
	m_pEquippedWeapon = m_pCharacter->GetEquipment().GetWeapon();

	if ( !IsProcessing() )
	{
		// acquire possible actions
		GetLegalWalkTiles();
		QueryAttackableTiles( m_AttackableCharacters );
	}

	if ( m_eState == ActionWalking )
	{
		if ( !m_pPathFollower->IsFollowingPath() )
		{
			m_eState = ActionIdle;

			// Are we walking to attack?
			if ( m_pEntityToAttack )
			{
				PathfindingNode* pNode = m_pPathGraph->VFindClosestNode( m_pEntityToAttack->GetTransform().GetPosition() );

				SelectNode( pNode );
				m_pEntityToAttack = NULL;
			}
		}
	}

	else if ( GetNumActions() == 0 )
	{
		Succeed();
	}
}

void CharacterControllerProcess::SetCharacter( CharacterComponent* pCharacter )
{
	m_pCharacter = pCharacter;
	m_pPathFollower = m_pCharacter->GetOwner()->GetComponent< PathFollowerComponent >();
	DungeonGame* pGame = (DungeonGame*)BaseApplication::Get()->GetProcessManager().GetProcessByName( "Game" );
	if ( pGame )
	{
		m_pPathGraph = pGame->GetWorld().GetGraph();
		GetLegalWalkTiles();
		QueryAttackableTiles( m_AttackableCharacters );
	}
}

void CharacterControllerProcess::QueryTileActions( PathfindingNode* pNode, std::vector< TileAction >& out )
{
	out.clear();

	if ( pNode->IsTraversable() && ( std::find( m_pWalkableNodes.begin(), m_pWalkableNodes.end(), pNode ) != m_pWalkableNodes.end() ) )
	{
		out.push_back( WalkTile );
		out.push_back( SearchTile );
	}

	else
	{
		Entity* pEntity = (Entity*)pNode->GetData();
		if ( pEntity )
		{
			if ( std::find( m_AttackableCharacters.begin(), m_AttackableCharacters.end(), pEntity ) != m_AttackableCharacters.end()  )
			{
				out.push_back( AttackTile );
			}
		}
	}
}

bool CharacterControllerProcess::SelectNode( PathfindingNode* pNode, TileAction eAction /*= Default */ )
{
	if ( std::find( m_pAttackableNodes.begin(), m_pAttackableNodes.end(), pNode ) != m_pAttackableNodes.end() )
	{
		Entity* pEntity = (Entity*)pNode->GetData();
		if ( pEntity )
		{
			RemoveAction( Attack );
			const Vector3& vTargetPosition = pEntity->GetTransform().GetPosition();
			if ( IsInWeaponRange( vTargetPosition ) )
			{
				pEntity->OnMessage( "Interact", m_pCharacter->GetOwner(), NULL );
			}

			else
			{
				PathfindingNode* pNode = FindClosestAdjacentNode( vTargetPosition );
				m_pEntityToAttack = pEntity;
				WalkTo( pNode );
			}
			
			return true;
		}
	}

	else if ( pNode->IsTraversable() && ( std::find( m_pWalkableNodes.begin(), m_pWalkableNodes.end(), pNode ) != m_pWalkableNodes.end() ) )
	{
		RemoveAction( Walk );
		WalkTo( pNode );

		return true;
	}

	return false;
}

void CharacterControllerProcess::QueryAttackableTiles( std::vector< Entity* >& out )
{
	// Clear the vector
	out.clear();
	m_pAttackableNodes.clear();

	if ( !IsActionAvailable( Attack ) )
		return;

	// Get the game for enemies list
	DungeonGame* pGame = (DungeonGame*)BaseApplication::Get()->GetProcessManager().GetProcessByName( "Game" );
	if ( !pGame )
		return;

	// Get the current weapon for the entity
	m_pEquippedWeapon = m_pCharacter->GetEquipment().GetWeapon();

	// Get the range
	float fWeaponRange = m_pEquippedWeapon->Range;
	float fWeaponRange2;

	if ( m_pEquippedWeapon->Range == 1.0f )
	{
		// Handle melee
		if ( IsActionAvailable( Walk ) )
		{
			float fSpeed = m_pCharacter->GetAttribute( Speed ).GetValue();
			fWeaponRange2 = m_pEquippedWeapon->Range + fSpeed;
		}

		else
		{
			fWeaponRange2 = 1.5f;
		}
		
		fWeaponRange2 *= fWeaponRange2 * 1.05f; // Added epsilon for floating errors;
	}

	else
	{
		// Ranged
		fWeaponRange2 = fWeaponRange * fWeaponRange * 1.05f; // Added epsilon for floating errors;
	}

	// Get the list of enemies
	if ( m_pCharacter->IsAI() )
	{
		// Use players
		const auto& players = pGame->GetWorld().GetPlayers();
		TestEnemiesInRange( fWeaponRange2, ( fWeaponRange == 1.0f ), players, out );
	}
	
	else
	{
		// Use AIs
		const auto& enemies = pGame->GetWorld().GetEnemies();
		TestEnemiesInRange( fWeaponRange2, ( fWeaponRange == 1.0f ), enemies, out );
	}

	if ( m_pAttackableNodes.empty() && !IsActionAvailable( Walk ) )
		RemoveAction( Attack );
}

void CharacterControllerProcess::TestEnemiesInRange( float fWeaponRange2, bool bMelee, const std::vector< CharacterComponent* >& enemies, std::vector< Entity* >& out )
{
	// Our character's position
	Vector3 vPosition = m_pCharacter->GetPosition();

	// Test enemies
	for ( auto it : enemies )
	{
		const Vector3& vEnemyPosition = it->GetPosition();
		float fDistance = vEnemyPosition.DistanceSQ( vPosition );
		if ( it != m_pCharacter && fDistance <= fWeaponRange2 )
		{
			if ( bMelee )
			{
				// If melee we must be able to walk next to the enemy
				if ( IsInWeaponRange( vEnemyPosition ) || FindClosestAdjacentNode( vEnemyPosition ) )
				{
					// If one is traversable in our range, add this enemy to the list
					out.push_back( it->GetOwner() );
					m_pAttackableNodes.push_back( m_pPathGraph->VFindClosestNode( it->GetPosition() ) );
				}
			}

			else
			{
				out.push_back( it->GetOwner() );
				m_pAttackableNodes.push_back( m_pPathGraph->VFindClosestNode( it->GetPosition() ) );
			}			
		}
	}	
}

PathfindingNode* CharacterControllerProcess::FindClosestAdjacentNode( const Vector3& vNodePosition )
{
	PathfindingNode* pClosestNode = NULL;
	float fClosestDistance = FLT_MAX;

	// Our character's position
	Vector3 vPosition = m_pCharacter->GetPosition();

	Vector3 vTestPosition;
	for ( int x = -1; x <= 1; ++x )
	{
		for ( int z = -1; z <= 1; ++z )
		{
			// Look at all neighbouring nodes
			vTestPosition.x = vNodePosition.x + x;
			vTestPosition.z = vNodePosition.z + z;

			PathfindingNode* pNode = m_pPathGraph->VFindClosestNode( vTestPosition );
			if ( pNode->IsTraversable() && ( std::find( m_pWalkableNodes.begin(), m_pWalkableNodes.end(), pNode ) != m_pWalkableNodes.end() ) )
			{
				// If one is traversable and in our range...
				float fDistance = vTestPosition.DistanceSQ( vPosition );
				if ( pClosestNode == NULL || fDistance < fClosestDistance )
				{
					fClosestDistance = fDistance;
					pClosestNode = pNode;
				}
			}
		}
	}

	return pClosestNode;
}

bool CharacterControllerProcess::IsInWeaponRange( const Vector3& vPosition )
{
	float fWeaponRange2 = m_pEquippedWeapon->Range * m_pEquippedWeapon->Range * 1.05 + 1.0f;
	if ( m_pCharacter->GetPosition().DistanceSQ( vPosition ) <= fWeaponRange2 )
	{
		return true;
	}

	return false;
}

void CharacterControllerProcess::WalkTo( PathfindingNode* pNode )
{
	PathfindingNode* pCurrentNode = m_pPathGraph->VFindClosestNode( m_pCharacter->GetPosition() );
	if ( pCurrentNode )
	{
		pCurrentNode->SetBlocked( false );
		pCurrentNode->SetData( NULL );
	}

	m_pPathFollower->SetDestination( pNode->GetPosition() );
	m_eState = ActionWalking;
}

void CharacterControllerProcess::WalkTo( const Vector3& vPosition )
{
	PathfindingNode* pNode = m_pPathGraph->VFindClosestNode( vPosition );
	PathfindingNode* pCurrentNode = m_pPathGraph->VFindClosestNode( m_pCharacter->GetPosition() );
	if ( pCurrentNode )
	{
		pCurrentNode->SetBlocked( false );
		pCurrentNode->SetData( NULL );
	}

	m_pPathFollower->SetDestination( pNode->GetPosition() );
}

bool CharacterControllerProcess::IsProcessing() const
{
	if ( m_eState != ActionIdle )
		return true;

	return false;
}

bool CharacterControllerProcess::IsActionAvailable( Actions eAction )
{
	if ( std::find( m_Actions.begin(), m_Actions.end(), eAction ) != m_Actions.end() )
	{
		return true;
	}

	return false;
}

void CharacterControllerProcess::AddAction( Actions eAction )
{
	m_Actions.push_back( eAction );
}

void CharacterControllerProcess::RemoveAction( Actions eAction )
{
	m_Actions.remove( eAction );
}

size_t CharacterControllerProcess::GetNumActions() const
{
	return m_Actions.size();
}
