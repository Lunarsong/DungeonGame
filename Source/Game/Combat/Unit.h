#pragma once
#include <Externals/HashedString/HashedString.h>
#include "Combat.h"
#include <Game/Entities/Component.h>

class UnitData : public Engine::ComponentData
{
public:
	UnitData();
	~UnitData();

	SET_TYPE( Unit );
	AUTO_SIZE;

	virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
	virtual bool VFromXML( tinyxml2::XMLElement* pData );

	const Damage& GetDamage() const { return m_Damage; }
	int GetMovement() const { return m_iMovement; }
	int GetHitPoints() const { return m_iHitPoints; }

public:
	Damage m_Damage;

	int m_iHitPoints;
	int m_iMovement;
	
};

class Unit : public Engine::Component
{
public:
	Unit(void);
	~Unit(void);

	SET_TYPE( Unit );

	const Damage& GetDamage() const { return ((const UnitData*)m_pData)->GetDamage(); }
	int GetMovement() const { return ((const UnitData*)m_pData)->GetMovement(); }

	virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
	virtual bool VFromXML( tinyxml2::XMLElement* pData );

private:

};