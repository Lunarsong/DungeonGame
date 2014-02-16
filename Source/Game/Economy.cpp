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
		pPrerequisite->SetAttribute( "Name", it.first.getStr().c_str() );
		pPrerequisite->SetAttribute( "Amount", it.second );

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
		m_Prerequisites[ pPrerequisite->Attribute( "Name" ) ] = pPrerequisite->IntAttribute( "Amount" );

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