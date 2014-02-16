#pragma once
#include <Externals/HashedString/HashedString.h>
#include "Combat.h"

class Unit : public Engine::IXMLResource
{
public:
	Unit(void);
	~Unit(void);

	const Damage& GetDamage() const { return m_Damage; }

	virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
	virtual bool VFromXML( tinyxml2::XMLElement* pData );

private:
	int m_iHitPoints;

	Damage m_Damage;

	int m_iAttack;
	int m_iDefense;

	int m_iInitiative;

	int m_iSpeed;

	int m_iAttackRange;
};