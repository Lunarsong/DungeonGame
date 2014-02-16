#include "Building.h"


Building::Building(void)
{
}


Building::~Building(void)
{
}

const std::map< HashedString, int >& Building::GetCost() const
{
	return m_Cost;
}
