//
//  Combat.cpp
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#include "Combat.h"

tinyxml2::XMLElement* Damage::VToXML( tinyxml2::XMLElement* pTo ) const
{
	pTo->SetAttribute( "Min", Min );
	pTo->SetAttribute( "Max", Max );

	return pTo;
}

bool Damage::VFromXML( tinyxml2::XMLElement* pData )
{
	pData->QueryIntAttribute( "Min", &Min );
	pData->QueryIntAttribute( "Max", &Max );

	return true;
}
