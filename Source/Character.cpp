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
	m_iLevel			= 1;
	m_iExperience		= 0;
	m_iAttributePoints	= 0;
	m_iTalentsPoints	= 0;

	m_uiConditions		= Alive;

	for ( int i = 0; i < AttributesCount; ++i )
	{
		GetAttribute( (Attributes)i ).SetBase( 10 );
		GetAttribute( (Attributes)i ).SetCap( 10 );
	}

	GetAttribute( HitPoints ).SetCap( 20 );
    GetAttribute( HitPoints ).SetBase( 20 );
    
    GetAttribute( Mana ).SetCap( 20 );
    GetAttribute( Mana ).SetBase( 20 );

	GetAttribute( Speed ).SetCap( 2 );

	CalculateSecondaryAttributes();
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
    if ( !CanAct() || !pVictim->IsAlive() )
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

		if ( !pVictim->IsAlive() )
		{
			AdjustExperience( pVictim->GetLevel() * 100 );
		}

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
		iExperience += i * 1000;
	}

	return iExperience;
}

void Character::HandleLevelUp()
{
	AdjustAttributePoints( 3 );
	AdjustTalentPoints( 1 );
	
	if ( m_pLevelUpCallback )
	{
		m_pLevelUpCallback( this );
	}
}

void Character::SetLevelUpCallback( std::function< void( Character* ) >& pCallback )
{
	m_pLevelUpCallback = pCallback;
}

void Character::SetAttributePoints( int iAttributePoints )
{
	m_iAttributePoints = iAttributePoints;
}

void Character::AdjustAttributePoints( int iAttributePoints )
{
	m_iAttributePoints += iAttributePoints;
}

int Character::GetAttributePoints() const
{
	return m_iAttributePoints;
}

void Character::BuyAttribute( Attributes eAttribute )
{
	if ( eAttribute >= Strength && eAttribute <= Charisma )
	{
		if ( m_iAttributePoints > 0 )
		{
			AdjustAttributePoints( -1 );
			m_Attributes[ eAttribute ].AdjustCap( 1 );
			m_Attributes[ eAttribute ].AdjustBase( 1 );

			CalculateSecondaryAttributes();
		}
	}
}

void Character::CalculateSecondaryAttributes()
{
	m_Attributes[ Speed ].SetCap( 1 + GetAttribute( Dexterity ).GetValue() * 0.25 );
	m_Attributes[ Speed ].SetBase( 1 + GetAttribute( Dexterity ).GetValue() * 0.25 );
}

double Character::GetProgressToNextLevel() const
{
	int iExperienceForThisLevel = CalculateExperienceForLevel( m_iLevel );
	int iExperienceForNextLevel = CalculateExperienceForLevel( m_iLevel + 1 );

	return (double)( m_iExperience - iExperienceForThisLevel) / (double)( iExperienceForNextLevel - iExperienceForThisLevel );
}

bool Character::IsAlive() const
{
	return ( m_Attributes[ HitPoints ].GetValue() > 0 );
}

int Character::GetTalentPoints() const
{
	return m_iTalentsPoints;
}

void Character::SetTalentPoints( int iTalentPoints )
{
	m_iTalentsPoints = iTalentPoints;
}

void Character::AdjustTalentPoints( int iAdjustment )
{
	m_iTalentsPoints += iAdjustment;
}

bool Character::BuyTalent( Talent* pTalent )
{
	return false;
}
