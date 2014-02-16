#include "Resources.h"


Resource::Resource(void)
{
	m_iAmount = 0;
	m_iIncome = 0;
}


Resource::~Resource(void)
{
}

int Resource::GetAmount() const
{
	return m_iAmount;
}

int Resource::GetIncome() const
{
	return m_iIncome;
}
