//
//  Ability.cpp
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#include "Ability.h"


Ability::Ability(void)
{
}


Ability::~Ability(void)
{
}

const std::string& Ability::GetDescription() const
{
	return m_Description;
}

void Ability::SetDescription( const std::string& strDescription )
{
	m_Description = strDescription;
}

int Ability::GetNumEffects() const
{
	return m_Effects.size();
}

const Ability::Effect& Ability::GetEffect( int iIndex )
{
	return m_Effects[ iIndex ];
}

tinyxml2::XMLElement* Ability::VToXML( tinyxml2::XMLElement* pTo ) const
{
	throw "Unimplemented";

	return NULL;
}

bool Ability::VFromXML( tinyxml2::XMLElement* pData )
{
	return true;
}

tinyxml2::XMLElement* Ability::Effect::VToXML( tinyxml2::XMLElement* pTo ) const
{
	throw "Unimplemented";

	return NULL;
}

bool Ability::Effect::VFromXML( tinyxml2::XMLElement* pData )
{
	tinyxml2::XMLElement* pDamageElement = pData->FirstChildElement( "Damage" );
	if ( pDamageElement )
	{
		pDamageElement->QueryIntAttribute( "Min", &mDamageMin );
		pDamageElement->QueryIntAttribute( "Max", &mDamageMax );

		const char* pType = pDamageElement->Attribute( "Type" );
		if ( pType )
		{
			if ( strcmp( pType, "Physical" ) == 0 )
			{
				mDamageType = Physical;
			}

			else if ( strcmp( pType, "Healing" ) == 0 )
			{
				mDamageType = Healing;
			}

			else if ( strcmp( pType, "Magical" ) == 0 )
			{
				mDamageType = Magical;
			}

			else if ( strcmp( pType, "Attribute" ) == 0 )
			{
				mDamageType = Attribute;
			}
		}

		pData->QueryIntAttribute( "Duration", &mDuration );

		const char* pParticles = pData->Attribute( "Particles" );
		if ( pParticles )
		{
			mParticles = pParticles;
		}
	}

	return true;
}
