#include "Stack.h"
#include <assert.h>
#include <Core/Math/RandomNumGen.h>


Stack::Stack(void)
{
}


Stack::~Stack(void)
{
}

const Unit* Stack::GetUnit() const
{
	return m_pUnit;
}

int Stack::GetAmount() const
{
	return m_iAmount;
}

void Stack::Attack( Stack& victim )
{
	assert( m_pUnit );

	const Damage& damage = m_pUnit->GetDamage();
	int iTotalDamage = 0;
	for ( int i = 0; i < m_iAmount; ++i )
	{
		iTotalDamage += Engine::g_RandomNumGen.RandomInt( damage.Min, damage.Max );
	}

	victim.OnDamage( iTotalDamage );
}

void Stack::OnDamage( int iDamage )
{
	m_iHealth -= iDamage;
}
