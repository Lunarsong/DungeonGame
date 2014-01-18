//
//  Character.h
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#pragma once

#include "Skill.h"
#include "Attribute.h"
#include "Equipment.h"
#include <Core/Math/Vector3.h>
#include <functional>

class Character
{
public:
    enum Condition
    {
        Alive,
        Dead,
        Frozen,
        Sleep,
        
        ConditionCount
    };
    
    Character();
    ~Character();
    
    Attribute& GetAttribute( Attributes eAttribute );
    
    bool Attack( Character* pVictim );
    void TakeDamage( short sDamage );
    
    bool CanAct() const;

	Equipment& GetEquipment();

	virtual const Engine::Vector3& GetPosition() const = 0;
    
	// Leveling
	int GetExperience() const;
	void SetExperience( int iExperience );
	void AdjustExperience( int iExperience );

	int GetLevel() const;
	void SetLevel( int iLevel );
	void AdjustLevel( int iLevel );

	static int CalculateExperienceForLevel( int iLevel );

	void SetLevelUpCallback( std::function< void( Character* ) >& pCallback );

protected:
	// Stats
    Attribute m_Attributes[ AttributesCount ];
    
	// Levels
	int m_iExperience;
	int m_iLevel;
	void CalculateLevel();
	void HandleLevelUp();

	std::function< void( Character* ) > m_pLevelUpCallback; // Called on level up

	// Equipment
	Equipment m_Equipment;


	unsigned int m_uiConditions;
    //
    virtual void OnDamage( short sDamage );
};