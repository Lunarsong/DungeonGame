#include "Unit.h"

bool Unit::VFromXML( tinyxml2::XMLElement* pData )
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

Unit::Unit()
{
	m_iHitPoints = 1;
	m_iMovement = 1;
}

Unit::~Unit()
{

}

tinyxml2::XMLElement* Unit::VToXML( tinyxml2::XMLElement* pTo ) const
{
	throw "Unimplemented";

	return pTo;
}

Engine::Component& Unit::operator=( const Component& other )
{
	const Unit& unit = (const Unit&)other;

	m_Damage		= unit.m_Damage;

	m_iHitPoints	= unit.m_iHitPoints;
	m_iMovement		= unit.m_iMovement;

	return *this;
}
