//
//  Character.cpp
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#include "Character.h"
#include <assert.h>

Character::Character()
{
    
}

Character::~Character()
{
    
}

bool Character::UseSkill( Skills eSkill, short sDifficulty )
{
    Skill skill = GetSkill( eSkill );
    if ( Skill::Check( skill, sDifficulty ) )
    {
        if ( skill.GainCheck( sDifficulty ) )
        {
            skill.SetBase( skill.GetBase() + 1 );
        }
        
        return true;
    }
    
    return false;
}

bool Character::UseSkill( Skills eSkill, short sDifficultyMin, short sDifficultyMax )
{
    Skill skill = GetSkill( eSkill );
    if ( Skill::Check( skill, sDifficultyMin, sDifficultyMax ) )
    {
        if ( skill.GainCheck( sDifficultyMin, sDifficultyMax ) )
        {
            skill.SetBase( skill.GetBase() + 1 );
        }
        
        return true;
    }
    
    return false;
}

Skill& Character::GetSkill( Skills eSkill )
{
    assert( eSkill < SkillsCount );
    
    return m_Skills[ eSkill ];
}