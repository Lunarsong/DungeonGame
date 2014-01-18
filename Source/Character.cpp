//
//  Character.cpp
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#include "Character.h"
#include <assert.h>
#include "Weapon.h"
#include <Core/Math/RandomNumGen.h>
#include <Core/EventManager/EventManager.h>
#include "CharacterEvents.h"

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

Attribute& Character::GetAttribute( Attributes eAttribute )
{
    assert( eAttribute < AttributesCount );
    
    return m_Attributes[ eAttribute ];
}

bool Character::Attack( Character* pVictim )
{
    if ( !CanAct() )
    {
        return false;
    }
    
    /*if ( UseSkill( Swords, pVictim->GetSkill( Swords ).GetValue() ) == true )
    {
        pVictim->TakeDamage( 1 );
    }*/

	Weapon* pWeapon = (Weapon*)m_Equipment.GetWeapon();
	float fDistance2 = GetPosition().DistanceSQ( pVictim->GetPosition() );
	float fRange2 = pWeapon->Range * pWeapon->Range * 1.05f + 1.0f; // Added epsilon for floating errors
	if ( fDistance2 <= fRange2 )
	{
		int iDamage = Engine::g_RandomNumGen.RandomInt( pWeapon->Damage.Min, pWeapon->Damage.Max );
		pVictim->TakeDamage( iDamage );

		return true;
	}
	
	return false;
}

void Character::TakeDamage( short sDamage )
{
    GetAttribute( HitPoints ).AdjustBase( -sDamage );
    
    OnDamage( sDamage );
}

void Character::OnDamage( short sDamage )
{
    if ( GetAttribute( HitPoints ).GetValue() <= 0 )
    {
        m_uiConditions = Dead;
		Engine::EventManager::TriggerEvent( Engine::Event( new EventCharacterDied( this ) ) );
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

Equipment& Character::GetEquipment()
{
	return m_Equipment;
}

int Character::GetExperience() const
{
	return m_iExperience;
}

void Character::SetExperience( int iExperience )
{
	AdjustExperience( iExperience - m_iExperience );
}

void Character::AdjustExperience( int iExperience )
{
	m_iExperience += iExperience;

	if ( iExperience < 0 )
	{

	}

	else
	{
		int iExperienceForNextLevel = CalculateExperienceForLevel( m_iLevel + 1 );
		while ( m_iExperience >= iExperienceForNextLevel )
		{
			if ( m_iExperience >= iExperienceForNextLevel )
			{
				m_iLevel += 1;

				HandleLevelUp();

				iExperienceForNextLevel = CalculateExperienceForLevel( m_iLevel + 1 );
			}
		}
	}
}

int Character::GetLevel() const
{
	return m_iLevel;
}

void Character::SetLevel( int iLevel )
{
	AdjustLevel( iLevel - GetLevel() );
}

void Character::AdjustLevel( int iLevel )
{
	int iNewLevel = GetLevel() + iLevel;
	int iExperienceNeeded = CalculateExperienceForLevel( iNewLevel );

	AdjustExperience( iExperienceNeeded - GetExperience() );
}

int Character::CalculateExperienceForLevel( int iLevel )
{
	int iExperience = 0;
	for ( int i = 1; i < iLevel; ++i )
	{
		iExperience += iLevel * 1000;
	}

	return iExperience;
}

void Character::HandleLevelUp()
{
	if ( m_pLevelUpCallback )
	{
		m_pLevelUpCallback( this );
	}
}

void Character::SetLevelUpCallback( std::function< void( Character* ) >& pCallback )
{
	m_pLevelUpCallback = pCallback;
}
