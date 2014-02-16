#pragma once

#include <Externals/HashedString/HashedString.h>
#include <map>

class Building
{
public:
	Building(void);
	~Building(void);

	HashedString	mName;

	int				mProductionTime;

	const std::map< HashedString, int >& GetCost() const;
	const std::map< HashedString, int >& GetUpkeep() const { return m_Upkeep; }
	const std::vector< HashedString >& GetUnitProduction() const { return m_UnitProduction; }

private:
	std::map< HashedString, int > m_Cost;
	std::map< HashedString, int > m_Upkeep;
	std::vector< HashedString > m_UnitProduction;
};