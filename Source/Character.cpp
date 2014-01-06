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
    m_uiConditions = Alive;
    
    GetAttribute( HitPoints ).SetBase( 20 );
    GetAttribute( HitPoints ).SetCap( 20 );
    
    GetAttribute( Mana ).SetBase( 20 );
    GetAttribute( Mana ).SetCap( 20 );
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
            skill.AdjustBase( 1 );
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

Attribute& Character::GetAttribute( Attributes eAttribute )
{
    assert( eAttribute < AttributesCount );
    
    return m_Attributes[ eAttribute ];
}

void Character::Attack( Character* pVictim )
{
    if ( !CanAct() )
    {
        return;
    }
    
    if ( UseSkill( Swords, pVictim->GetSkill( Swords ).GetValue() ) == true )
    {
        pVictim->TakeDamage( 1 );
    }
}

void Character::TakeDamage( short sDamage )
{
    GetAttribute( HitPoints ).AdjustModifier( -sDamage );
    
    OnDamage( sDamage );
}

void Character::OnDamage( short sDamage )
{
    if ( GetAttribute( HitPoints ).GetValue() <= 0 )
    {
        m_uiConditions = Dead;
    }
}

bool Character::CanAct() const
{
    if ( m_uiConditions == Dead )
    {
        return false;
    }
    
    return true;
}