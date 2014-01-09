//
//  CharacterComponent.cpp
//  DungeonGame
//
//  Created by Shanee on 1/5/14.
//
//

#include "CharacterComponent.h"
#include <Game/Entities/Entity.h>
#include <Game/Entities/Components/Rendering/MeshComponent.h>
#include <Engine.h>

#include "DungeonGame.h"

using namespace Engine;

CharacterComponent::CharacterComponent()
{
    m_bAI = true;
}

CharacterComponent::~CharacterComponent()
{
    
}

const HashedString CharacterComponent::g_hType( "Character" );

const HashedString& CharacterComponent::GetType() const
{
    return g_hType;
}

void CharacterComponent::VStart()
{
    
}

void CharacterComponent::VEnd()
{
    
}

void CharacterComponent::VUpdate( float fDeltaSeconds )
{
    
}

bool CharacterComponent::VOnMessage( const HashedString& hMessage, Entity* pMessenger, const void* pData )
{
    if ( hMessage == "Interact" )
    {
        if ( pMessenger )
        {
            CharacterComponent* pOther = pMessenger->GetComponent< CharacterComponent >();
            if ( pOther )
            {
                pOther->Attack( this );
                
                Attack( pOther );
            }
        }
        return true;
    }
    
    return false;
}

void CharacterComponent::OnDamage( short sDamage )
{
    Character::OnDamage( sDamage );
    
    MeshComponent* pMesh = m_pOwner->GetComponent<MeshComponent>();
    if ( pMesh )
    {
        StructuredMaterial<ColorF>* pMaterial = (StructuredMaterial<ColorF>*)pMesh->GetMaterial();
     
        double dPercent = GetAttribute( HitPoints ).GetPercent();
        pMaterial->GetData().Red = dPercent;
        pMaterial->GetData().Green = dPercent * 0.7f;
        pMaterial->GetData().Blue = dPercent * 0.7f;
    }
}