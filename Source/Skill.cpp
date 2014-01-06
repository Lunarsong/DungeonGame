//
//  Skill.cpp
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#include "Skill.h"
#include <Core/Application/BaseApplication.h>

Skill::Skill()
: m_hName( "Unnamed" )
{
    m_sCap = 1000;
    
    m_sModifier = 0;
    m_sBase = 0;
}

Skill::~Skill()
{
    
}

const HashedString& Skill::GetName() const
{
    return m_hName;
}

short Skill::GetBase() const
{
    return m_sBase;
}

short Skill::GetCap() const
{
    return m_sCap;
}

short Skill::GetModifier() const
{
    return m_sModifier;
}

short Skill::GetValue() const
{
    short sTotal = ( m_sBase + m_sModifier );

    if ( sTotal > m_sCap )
    {
        return m_sCap;
    }
    
    return sTotal;
}

void Skill::SetName( const HashedString& hName )
{
    m_hName = hName;
}

void Skill::SetBase( short sBase )
{
    if ( sBase > m_sCap )
    {
        m_sBase = m_sCap;
    }
    
    else
    {
        m_sBase = sBase;
    }
}

void Skill::SetCap( short sCap )
{
    m_sCap = sCap;
    
    if ( m_sBase > sCap )
    {
        m_sBase = sCap;
    }
}

void Skill::SetModifier( short sModifier )
{
    m_sModifier = sModifier;
}

void Skill::AdjustBase( short sValue )
{
    SetBase( GetBase() + 1 );
}

void Skill::AdjustModifier( short sValue )
{
    SetModifier( GetModifier() + 1 );
}

void Skill::AdjustCap( short sValue )
{
    SetCap( GetCap() + 1 );
}

double Skill::Value() const
{
    return ((double)GetValue() / 10.0 );
}

double Skill::Base() const
{
    return ((double)m_sBase / 10.0 );
}

double Skill::Cap() const
{
    return ((double)m_sCap / 10.0 );
}

double Skill::Modifier() const
{
    return ((double)m_sModifier / 10.0 );
}

bool Skill::Check( const Skill& skill1, const Skill& skill2 )
{
    return Check( skill1, skill2.GetValue() );
}

bool Skill::Check( const Skill& skill, short sDifficulty )
{
    // Calculate chance
    double dChance = ( skill.Value() + 20.0 ) / ( ( (double)sDifficulty / 10.0 + 20.0 ) * 2.0 );
    
    // Get random value
    double dRandom = Engine::g_RandomNumGen.RandomDouble();
    
    // return result
    return ( dRandom <= dChance );
}

bool Skill::Check( const Skill& skill, short sMin, short sMax )
{
    short sValue = skill.GetValue();
    
    if ( sValue < sMin )
    {
        return false;
    }
    
    else if ( sValue >= sMax )
    {
        return true;
    }
    
    // Calculate chance
    short sDifference = sMax - sMin;
    sValue -= sMin;
    
    double dChance = (double)sValue / (double)sDifference;
    
    // Get random value
    double dRandom = Engine::g_RandomNumGen.RandomDouble();
    
    // return result
    return ( dRandom <= dChance );
}

bool Skill::GainCheck()
{
    // Get random value
    double dRandom = Engine::g_RandomNumGen.RandomDouble();
    
    // Chance to gain
    const double k_dGainThreshold = 0.5;
    if ( dRandom < k_dGainThreshold )
        return false;
    
    // Chance based on level
    double dCapped = (double)GetBase() / (double)GetCap();
    
    double dChance = 1.0 - dCapped;
    if ( dChance < 0.1 )
    {
        dChance = 0.1;
    }
    
    dRandom = Engine::g_RandomNumGen.RandomDouble();
    
    return ( dRandom <= dChance );
}

bool Skill::GainCheck( short sDifficulty )
{
    return GainCheck( sDifficulty, sDifficulty + 200 );
}

bool Skill::GainCheck( short sDifficultyMin, short sDifficultyMax )
{
    short sValue = GetBase();
    if ( sValue < sDifficultyMin || sValue >= sDifficultyMax )
    {
        return false;
    }
    
    if ( GainCheck() )
    {
        sValue -= sDifficultyMin;
        short sDifference = sDifficultyMax - sDifficultyMin;
        
        double dChance = 1.0 - (double)sValue / (double)sDifference;
        
        if ( dChance < 0.1 )
        {
            dChance = 0.1;
        }
        
        double dRandom = Engine::g_RandomNumGen.RandomDouble();
        
        return ( dRandom <= dChance );
    }
    
    return false;
}