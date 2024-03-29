//
//  Attribute.h
//  DungeonGame
//
//  Created by Shanee on 1/5/14.
//
//

#pragma once

enum Attributes
{
	// Attributes
    Health,
    Mana,
    
	// Stats
    Strength,
	Constitution,
	Dexterity,
    Intelligence,
    Willpower,
	Charisma,

	// 
    Speed,
    
    AttributesCount
};

class Attribute
{
public:
    Attribute();
    ~Attribute();
    
    short GetValue() const;
    short GetBase() const;
    short GetModifier() const;
    short GetCap() const;
    
    void SetBase( short sValue );
    void SetModifier( short sValue );
    void SetCap( short sValue );
    
    void AdjustBase( short sValue );
    void AdjustModifier( short sValue );
    void AdjustCap( short sValue );
    
    double GetPercent() const;
    
private:
    short   m_sBase;
    short   m_sModifier;
    short   m_sCap;
};