#include "Economy.h"
#include <Core/Utils/Macros.h>

Economy::Economy(void)
{

}


Economy::~Economy(void)
{
}

Producible::Producible()
{
	m_eType = Structure;
	m_usProductionTime = 1;
}

Producible::~Producible()
{

}

tinyxml2::XMLElement* Producible::VToXML( tinyxml2::XMLElement* pTo ) const
{
	pTo->SetAttribute( "ProductionTime", m_usProductionTime );

	for ( auto it : m_Cost )
	{
		tinyxml2::XMLElement* pCost = pTo->GetDocument()->NewElement( "Cost" );
		pCost->SetAttribute( "Resource", it.first.getStr().c_str() );
		pCost->SetAttribute( "Amount", it.second );
		
		pTo->LinkEndChild( pCost );
	}

	for ( auto it : m_Upkeep )
	{
		tinyxml2::XMLElement* pUpkeep = pTo->GetDocument()->NewElement( "Upkeep" );
		pUpkeep->SetAttribute( "Resource", it.first.getStr().c_str() );
		pUpkeep->SetAttribute( "Amount", it.second );

		pTo->LinkEndChild( pUpkeep );
	}

	for ( auto it : m_Prerequisites )
	{
		tinyxml2::XMLElement* pPrerequisite = pTo->GetDocument()->NewElement( "Prerequisite" );
		it.VToXML( pPrerequisite );

		pTo->LinkEndChild( pPrerequisite );
	}

	return pTo;
}

bool Producible::VFromXML( tinyxml2::XMLElement* pData )
{
	const char* pProductionTime = pData->Attribute( "ProductionTime" );
	if ( pProductionTime )
	{
		FromString( m_usProductionTime, pProductionTime );
	}

	const char* pIcon = pData->Attribute( "Icon" );
	if ( pIcon )
	{
		m_Icon = pIcon;
	}

	tinyxml2::XMLElement* pCost = pData->FirstChildElement( "Cost" );
	while ( pCost )
	{
		m_Cost[ pCost->Attribute( "Resource" ) ] = pCost->IntAttribute( "Amount" );

		pCost = pCost->NextSiblingElement( "Cost" );
	}

	tinyxml2::XMLElement* pUpkeep = pData->FirstChildElement( "Upkeep" );
	while ( pUpkeep )
	{
		m_Upkeep[ pUpkeep->Attribute( "Resource" ) ] = pUpkeep->IntAttribute( "Amount" );

		pUpkeep = pUpkeep->NextSiblingElement( "Upkeep" );
	}

	tinyxml2::XMLElement* pPrerequisite = pData->FirstChildElement( "Prerequisite" );
	while ( pPrerequisite )
	{
		Prerequisite preq;
		preq.VFromXML( pPrerequisite );
		m_Prerequisites.push_back( preq );

		pPrerequisite = pPrerequisite->NextSiblingElement( "Prerequisite" );
	}

	const char* pType = pData->Attribute( "Type" );
	if ( pType )
	{
		if ( strcmp( pType, "Unit" ) == 0 )
		{
			m_eType = Unit;
		}
	}

	return true;
}

tinyxml2::XMLElement* Producible::Prerequisite::VToXML( tinyxml2::XMLElement* pTo ) const
{
	throw "Unimplemented";
}

bool Producible::Prerequisite::VFromXML( tinyxml2::XMLElement* pData )
{
	pData->QueryIntAttribute( "Amount", &mAmount );
	mName = pData->Attribute( "Name" );
	const char* pLevel = pData->Attribute( "Level" );
	if ( pLevel )
	{
		if ( strcmp( pLevel, "City" ) == 0 )
		{
			mLevel = City;
		}

		else if ( strcmp( pLevel, "Faction" ) == 0 )
		{
			mLevel = Faction;
		}
	}


	return true;
}

Producible::Prerequisite::Prerequisite()
{
	mAmount = 1;
}
