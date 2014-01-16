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
    
    bool UseSkill( Skills eSkill, short sDifficulty );
    bool UseSkill( Skills eSkill, short sDifficultyMin, short sDifficultyMax );
    
    Skill& GetSkill( Skills eSkill );
    Attribute& GetAttribute( Attributes eAttribute );
    
    bool Attack( Character* pVictim );
    void TakeDamage( short sDamage );
    
    bool CanAct() const;

	Equipment& GetEquipment();

	virtual const Engine::Vector3& GetPosition() const = 0;
    
protected:
    Skill m_Skills[ SkillsCount ];
    Attribute m_Attributes[ AttributesCount ];
    
	Equipment m_Equipment;

    unsigned int m_uiConditions;
    
    //
    virtual void OnDamage( short sDamage );
};