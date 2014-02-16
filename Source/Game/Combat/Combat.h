//
//  Combat.h
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#pragma once

#include <Core/Resources/ISerializable.h>

class Combat
{
public:
    
    
private:
    
    
};

enum DamageType
{
	Undefined,
	Physical,
	Magical,
	Healing,
	Attribute,

	DamageTypeCount	
};

struct Damage : public Engine::IXMLResource
{
	int Min;
	int Max;
	DamageType Type;

	virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
	virtual bool VFromXML( tinyxml2::XMLElement* pData );
};

enum Target
{
	Self,
	Character,
	Ground
};