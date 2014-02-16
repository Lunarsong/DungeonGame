#pragma once

#include "../Combat/Army.h"
#include "City.h"
#include "../Economy.h"
#include <map>
#include <vector>

class Faction
{
public:
	Faction(void);
	~Faction(void);

	int GetResourceAmount( const HashedString& hResource ) const;
	void AdjustResource( const HashedString& hResource, int iAmount );

	bool CanPayCost( const std::map< HashedString, int >& cost ) const;
	bool PayCost( const std::map< HashedString, int >& cost );
	void AddBulkResources( const std::map< HashedString, int >& resources );

	void AdjustProduction( const HashedString& hResource, int iAmount );
	void AdjustUpkeep( const HashedString& hResource, int iAmount );

	void Produce();
	void PayUpkeep();

	void AddCity( City* pCity );
	void RemoveCity( City* pCity );

	void OnTurnStart();
	void OnTurnEnd();

private:
	std::vector< City* >			m_Cities;
	std::vector< Army* >			m_Armies;

	std::map< HashedString, int >	m_Resources;

	std::map< HashedString, int >	m_Production;
	std::map< HashedString, int >	m_Upkeep;
};

