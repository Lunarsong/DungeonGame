#include "Tile.h"


Tile::Tile(void)
{
	mName = "Unnamed Tile";
	mWeight = 0;
	mProduction = 0;
}


Tile::~Tile(void)
{
}

tinyxml2::XMLElement* Tile::VToXML( tinyxml2::XMLElement* pTo ) const
{
	throw "Unimplemented";

	return pTo;
}

bool Tile::VFromXML( tinyxml2::XMLElement* pData )
{
	const char* pName = pData->Attribute( "Name" );
	if ( pName )
	{
		mName = pName;
	}

	pData->QueryIntAttribute( "Weight", &mWeight );

	tinyxml2::XMLElement* pResource = pData->FirstChildElement( "Resource" );
	if ( pResource )
	{
		const char* pResourceName = pResource->Attribute( "Name" );
		if ( pResourceName )
		{
			mResource = pResourceName;
			pResource->QueryIntAttribute( "Production", &mProduction );
		}
	}

	return true;
}
