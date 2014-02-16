//
//  Skill.h
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#pragma once

#include <Externals/HashedString/HashedString.h>

enum Skills
{
    Swords,
    Fencing,
    Magic,
    Lockpicking,
    
    SkillsCount
};

class Skill
{
public:
    Skill();
    ~Skill();
    
    const HashedString& GetName() const;
    
    short GetBase() const;
    short GetCap() const;
    short GetModifier() const;
    short GetValue() const;
    
    void SetName( const HashedString& hName );
    void SetBase( short sBase );
    void SetCap( short sCap );
    void SetModifier( short sModifier );
    
    void AdjustBase( short sValue );
    void AdjustModifier( short sValue );
    void AdjustCap( short sValue );
    
    double Value() const;
    double Base() const;
    double Cap() const;
    double Modifier() const;
    
    static bool Check( const Skill& skill1, const Skill& skill2 );
    static bool Check( const Skill& skill, short sDifficulty );
    static bool Check( const Skill& skill, short sMin, short sMax );
    
    bool GainCheck();
    bool GainCheck( short sDifficulty );
    bool GainCheck( short sDifficultyMin, short sDifficultyMax );
    
private:
    HashedString m_hName;
    short m_sBase;
    short m_sCap;
    short m_sModifier;
};