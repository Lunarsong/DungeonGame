//
//  Attribute.cpp
//  DungeonGame
//
//  Created by Shanee on 1/5/14.
//
//

#include "Attribute.h"

Attribute::Attribute()
{
    m_sBase = 4;
    m_sCap = 100;
    m_sModifier = 0;
}

Attribute::~Attribute()
{
    
}

short Attribute::GetValue() const
{
    return m_sBase + m_sModifier;
}

short Attribute::GetBase() const
{
    return m_sBase;
}

short Attribute::GetModifier() const
{
    return m_sModifier;
}

short Attribute::GetCap() const
{
    return m_sCap;
}

void Attribute::SetBase( short sValue )
{
    if ( sValue < m_sCap )
    {
        m_sBase = sValue;
    }
    
    else
    {
        m_sBase = m_sCap;
    }
}

void Attribute::SetModifier( short sValue )
{
    m_sModifier = sValue;
}

void Attribute::SetCap( short sValue )
{
    m_sCap = sValue;
    
    if ( m_sBase > m_sCap )
    {
        m_sBase = sValue;
    }
}

void Attribute::AdjustBase( short sValue )
{
    SetBase( GetBase() + sValue );
}

void Attribute::AdjustModifier( short sValue )
{
    SetModifier( GetModifier() + sValue );
}

void Attribute::AdjustCap( short sValue )
{
    SetCap( GetCap() + sValue );
}

double Attribute::GetPercent() const
{
    return (double)GetValue() / (double)GetCap();
}