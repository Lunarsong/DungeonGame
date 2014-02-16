#pragma once

#include <Externals/HashedString/HashedString.h>
#include <Core/Resources/ISerializable.h>

class Tile : public Engine::IXMLResource
{
public:
	Tile(void);
	~Tile(void);

	HashedString	mName;
	HashedString	mResource;
	int				mProduction;

	int				mWeight;

	virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
	virtual bool VFromXML( tinyxml2::XMLElement* pData );
};

