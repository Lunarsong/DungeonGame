#include "Unit.h"


Unit::Unit(void)
{

}


Unit::~Unit(void)
{
}

tinyxml2::XMLElement* Unit::VToXML( tinyxml2::XMLElement* pTo ) const
{
	throw "Unimplemented";

	return pTo;
}

bool Unit::VFromXML( tinyxml2::XMLElement* pData )
{
	throw "Unimplemented";

	return true;
}

tinyxml2::XMLElement* UnitData::VToXML( tinyxml2::XMLElement* pTo ) const
{
	throw "Unimplemented";

	return pTo;
}

bool UnitData::VFromXML( tinyxml2::XMLElement* pData )
{
	tinyxml2::XMLElement* pDamage = pData->FirstChildElement( "Damage" );
	if ( pDamage )
	{
		m_Damage.VFromXML( pDamage );
	}

	pData->QueryIntAttribute( "HP", &m_iHitPoints );
	pData->QueryIntAttribute( "Movement", &m_iMovement );

	return true;
}

UnitData::UnitData()
{
	m_iHitPoints = 1;
	m_iMovement = 1;
}

UnitData::~UnitData()
{

}
