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
    
    void Attack( Character* pVictim );
    void TakeDamage( short sDamage );
    
    bool CanAct() const;
    
protected:
    Skill m_Skills[ SkillsCount ];
    Attribute m_Attributes[ AttributesCount ];
    
    unsigned int m_uiConditions;
    
    //
    virtual void OnDamage( short sDamage );
};