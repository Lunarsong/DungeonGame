//
//  CharacterComponent.h
//  DungeonGame
//
//  Created by Shanee on 1/5/14.
//
//

#pragma once

#include <Game/Entities/Component.h>
#include "Character.h"

class CharacterComponent : public Engine::Component, public Character
{
public:
    CharacterComponent();
    virtual ~CharacterComponent();
    
    static const HashedString g_hType;
    
    virtual const HashedString& GetType() const;
    
    virtual void VStart();
    virtual void VEnd();
    
    virtual void VUpdate( float fDeltaSeconds );
    
    virtual bool VOnMessage( const HashedString& hMessage, Engine::Entity* pMessenger, const void* pData );
    
protected:
    bool m_bAI;

    virtual void OnDamage( short sDamage );
};