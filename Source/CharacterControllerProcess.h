#pragma once

#include <Core/Process/Process.h>
#include <Core/Input/InputHandlers.h>
#include <Game/Entities/Components/AI/PathFollowerComponent.h>
#include <UI/UserInterface.h>

#include "CharacterComponent.h"
#include "GameMenu.h"
#include "InventoryMenu.h"
#include "CharacterMenu.h"

using namespace Engine;

class CharacterControllerProcess : public Process
{
public:
	CharacterControllerProcess(void);
	~CharacterControllerProcess(void);

	virtual void VOnInit();
	virtual void VOnSuccess();
	virtual void VOnFail();
	virtual void VOnAbort();

	virtual void VOnUpdate( const float fDeltaSeconds );

	void SetCharacter( CharacterComponent* pCharacter );

	enum TileAction
	{
		None,
		WalkTile,
		AttackTile,
		SearchTile,
		UseTile,

		Default
	};

	void QueryTileActions( PathfindingNode* pNode, std::vector< TileAction >& out );
	void QueryAttackableTiles( std::vector< Entity* >& out );
	bool SelectNode( PathfindingNode* pNode, TileAction eAction = Default );
	
	enum ActionState
	{
		ActionIdle,
		ActionWalking,
		ActionAttacking,

		ActionStateCount
	};

	enum Actions
	{
		Attack,
		Walk
	};
	bool IsActionAvailable( Actions eAction );
	void AddAction( Actions eAction );
	void RemoveAction( Actions eAction );
	size_t GetNumActions() const;

	bool IsProcessing() const;

protected:
	ActionState m_eState;

	SmartPtr<CharacterComponent> m_pCharacter;
	SmartPtr<PathFollowerComponent> m_pPathFollower;

	SmartPtr< IPathfindingGraph > m_pPathGraph;
	std::vector< PathfindingNode* > m_pWalkableNodes;
	std::vector< PathfindingNode* > m_pAttackableNodes;

	std::vector< Entity* > m_AttackableCharacters;
	PathfindingNode* m_pTargetNode;

	std::list< Actions> m_Actions;

	Entity* m_pEntityToAttack;

	void GetLegalWalkTiles();

	Weapon* m_pEquippedWeapon;

	void TestEnemiesInRange( float fWeaponRange2, bool bMelee, const std::vector< CharacterComponent* >& enemies, std::vector< Entity* >& out );
	PathfindingNode* FindClosestAdjacentNode( const Vector3& vNodePosition );

	bool IsInWeaponRange( const Vector3& vPosition );
	void WalkTo( PathfindingNode* pNode );
	void WalkTo( const Vector3& vPosition );

};


