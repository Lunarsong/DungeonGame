#include "Faction.h"


Faction::Faction(void)
{
}


Faction::~Faction(void)
{
}

int Faction::GetResourceAmount( const HashedString& hResource ) const
{
	std::map< HashedString, int >::const_iterator pIter = m_Resources.find( hResource );
	if ( pIter != m_Resources.end() )
	{
		return pIter->second;
	}

	return 0;
}

void Faction::AdjustResource( const HashedString& hResource, int iAmount )
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
}

bool Faction::PayCost( const std::map< HashedString, int >& cost )
{
	if ( CanPayCost( cost ) )
	{
		for ( auto it : cost )
		{
			AdjustResource( it.first, -it.second );
		}

		return true;
	}

	return false;
}

void Faction::AddBulkResources( const std::map< HashedString, int >& cost )
{
	for ( auto it : cost )
	{
		AdjustResource( it.first, it.second );
	}
}

bool Faction::CanPayCost( const std::map< HashedString, int >& cost ) const
{
	for ( auto it : cost )
	{
		if ( GetResourceAmount( it.first ) < it.second )
		{
			return false;
		}
	}

	return true;
}

void Faction::Produce()
{
	for ( auto it : m_Production )
	{
		AdjustResource( it.first, it.second );
	}
}

void Faction::PayUpkeep()
{
	for ( auto it : m_Production )
	{
		AdjustResource( it.first, -it.second );
	}
}

void Faction::AdjustProduction( const HashedString& hResource, int iAmount )
{
	std::map< HashedString, int >::iterator pIter = m_Production.find( hResource );
	if ( pIter != m_Production.end() )
	{
		pIter->second += iAmount;
	}

	else
	{
		m_Production[ hResource ] = iAmount;
	}
}

void Faction::AdjustUpkeep( const HashedString& hResource, int iAmount )
{
	std::map< HashedString, int >::iterator pIter = m_Upkeep.find( hResource );
	if ( pIter != m_Upkeep.end() )
	{
		pIter->second += iAmount;
	}

	else
	{
		m_Upkeep[ hResource ] = iAmount;
	}
}

void Faction::AddCity( City* pCity )
{
	m_Cities.push_back( pCity );
	pCity->UpdateProducibles();
}

void Faction::RemoveCity( City* pCity )
{
	for ( std::vector< City* >::iterator pIter = m_Cities.begin(); pIter != m_Cities.end(); ++pIter )
	{
		if ( (*pIter) == pCity )
		{
			m_Cities.erase( pIter );
			return;
		}
	}
}

void Faction::OnTurnStart()
{
	Produce();

	PayUpkeep();

	for ( auto it : m_Cities )
	{
		it->Update();
	}
}

void Faction::OnTurnEnd()
{

}
