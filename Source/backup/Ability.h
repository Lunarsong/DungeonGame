//
//  Ability.h
//  DungeonGame
//
//  Created by Shanee on 1/4/14.
//
//

#ifndef __DungeonGame__Ability__
#define __DungeonGame__Ability__

#include <iostream>
#include <Externals/HashedString/HashedString.h>
#include "Combat.h"
#include <vector>
#include <Core/Resources/ISerializable.h>

using namespace Engine;

class Ability : public IXMLResource
{
public:
	Ability(void);
	~Ability(void);

	struct Effect : public IXMLResource
	{
		Target	mTarget;
		int		mDamageMin;
		int		mDamageMax;
		DamageType mDamageType;

		int		mDuration;

		std::string mParticles;

		virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
		virtual bool VFromXML( tinyxml2::XMLElement* pData );
	};

	const std::string& GetDescription() const;
	void SetDescription( const std::string& strDescription );

	int GetNumEffects() const;
	const Effect& GetEffect( int iIndex );

	virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
	virtual bool VFromXML( tinyxml2::XMLElement* pData );

private:
	HashedString m_hName;

	std::string m_Description;
	std::vector< Effect > m_Effects;

};

#endif /* defined(__DungeonGame__Ability__) */
