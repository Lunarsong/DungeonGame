#include "City.h"
#include "Faction.h"

#include <assert.h>
#include "../GameData.h"
#include <Game/Entities/Entity.h>

City::City(void)
{
	m_Faction = NULL;

	for ( int i = 0; i < Producible::TypeCount; ++i )
	{
		m_Production[ i ].reserve( 10 );
	}	
}


City::~City(void)
{
}

void City::Update()
{
	UpdateProduction();
}

void City::UpdateProduction()
{
	for ( int i = 0; i < Producible::TypeCount; ++i )
	{
		if ( m_Production[ i ].size() )
		{
			m_Production[ i ][ 0 ].mTurns -= 1;
			if ( m_Production[ i ][ 0 ].mTurns <= 0 )
			{
				FinishProduction( m_Production[ i ][ 0 ].mProduct, m_Production[ i ][ 0 ].mAmount );
				m_Production[ i ].erase( m_Production[ i ].begin() );

				UpdateProducibles();
			}
		}	
	}
}

void City::FinishProduction( const HashedString& hProduction, int iAmount )
{
	AdjustResource( hProduction, iAmount );

	m_Faction->AdjustProduction( hProduction, iAmount );

	const Engine::Entity* pData = FindProducible( hProduction );
	if ( pData )
	{
		Engine::Entity* pEntity = Engine::Entity::Instantiate( pData );
		pEntity->SetTransform( m_pOwner->GetTransform() );
	}

	else
	{
		throw "Missing data";
	}
}

void City::SetFaction( Faction* pFaction )
{
	if ( m_Faction == pFaction )
		return;

	if ( m_Faction )
	{
		m_Faction->RemoveCity( this );
	}

	m_Faction = pFaction;

	if ( m_Faction )
	{
		m_Faction->AddCity( this );
	}
}

Faction* City::GetFaction()
{
	return m_Faction;
}

void City::SetName( const HashedString& hName )
{
	m_hName = hName;
}

const HashedString& City::GetName() const
{
	return m_hName;
}

void City::Build( const HashedString& hName )
{
	StartProduction( hName );
}

void City::CancelBuild( Producible::Type eProductionType, int iIndex )
{
	if ( !(m_Faction && m_Production[ eProductionType ].size() > iIndex ) )
	{
		return;
	}

	std::vector< Production >::const_iterator iter = m_Production[ eProductionType ].begin() + iIndex;
	for ( auto it : iter->mResources )
	{
		m_Faction->AdjustResource( it.first, it.second );
	}
}

void City::StartProduction( const HashedString& hName )
{
	const Entity* pEntity = NULL;
	for ( auto it : m_Producibles )
	{
		if ( it->GetName() == hName.getStr() )
		{
			pEntity = it;
			break;
		}
	}

	const Producible* pProduct = (const Producible*)pEntity->GetComponent( Producible::GetComponentType() );

	const auto& cost = pProduct->GetCost();
	if ( m_Faction->PayCost( cost ) )
	{
		Production prod;
		prod.mProduct = pEntity->GetName();
		prod.mAmount = 1;
		prod.mResources = cost;
		prod.mTurns = prod.mTurnsLeft = pProduct->GetProductionTime();		

		m_Production[ pProduct->GetType() ].push_back( prod );
	}
}

void City::UpdateProducibles()
{
	m_Producibles.clear();

	auto& producibles = GameData::Get().GetProducibles();
	for ( auto it : producibles )
	{
		if ( VerifyPrerequisites( *it.second ) )
		{
			m_Producibles.push_back( GameData::Get().GetEntity( it.first ) );
		}
		
	}
}

bool City::VerifyPrerequisites( const Producible& producible ) const
{
	const auto& prerequisites = producible.GetPrerequisite();
	for ( const auto& it : prerequisites )
	{
		if ( it.mLevel == Producible::Prerequisite::City )
		{
			if ( GetResourceAmount( it.mName ) < it.mAmount )
			{
				return false;
			}
		}

		else if ( it.mLevel == Producible::Prerequisite::Faction )
		{
			if ( m_Faction->GetResourceAmount( it.mName ) < it.mAmount )
			{
				//return false;
			}
		}
	}

	return true;
}

/*tinyxml2::XMLElement* CityData::VToXML( tinyxml2::XMLElement* pTo ) const
{
	throw "Unimplemented";

	return pTo;
}

bool CityData::VFromXML( tinyxml2::XMLElement* pData )
{
	throw "Unimplemented";

	tinyxml2::XMLElement* pConstructible = pData->FirstChildElement( "Builds" );
	while ( pConstructible )
	{


		pConstructible = pConstructible->NextSiblingElement( "Builds" );
	}

	return true;
}*/

int City::GetResourceAmount( const HashedString& hResource ) const
{
	std::map< HashedString, int >::const_iterator pIter = m_Resources.find( hResource );
	if ( pIter != m_Resources.end() )
	{
		return pIter->second;
	}

	return 0;
}

void City::AdjustResource( const HashedString& hResource, int iAmount )
{
	std::map< HashedString, int >::iterator pIter = m_Resources.find( hResource );
	if ( pIter != m_Resources.end() )
	{
		pIter->second += iAmount;
	}

	else
	{
		m_Resources[ hResource ] = iAmount;
	}	

	UpdateProducibles();
}

const Engine::Entity* City::FindProducible( const HashedString& hName ) const
{
	for ( const auto& it : m_Producibles )
	{
		if ( it->GetName() == hName.getStr() )
		{
			return it;
		}
	}

	return NULL;
}

Component& City::operator=( const Component& other )
{
	const City& castOther = (const City&)other;

	m_Faction = castOther.m_Faction;
	m_hName = castOther.m_hName;
	m_Producibles = castOther.m_Producibles;
	m_Resources = castOther.m_Resources;

	for ( int i = 0; i < Producible::TypeCount; ++i )
	{
		m_Production[ i ] = castOther.m_Production[ i ];
	}

	return *this;
}
