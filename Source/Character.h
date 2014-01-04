//
//  Character.h
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#pragma once

#include "Skill.h"

class Character
{
public:
    Character();
    ~Character();
    
    bool UseSkill( Skills eSkill, short sDifficulty );
    bool UseSkill( Skills eSkill, short sDifficultyMin, short sDifficultyMax );
    
    Skill& GetSkill( Skills eSkill );
    
private:
    std::string m_strName;
    
    Skill m_Skills[ SkillsCount ];
    
};