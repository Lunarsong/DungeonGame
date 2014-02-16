#pragma once

#include "Unit.h"

class Stack
{
public:
	Stack(void);
	~Stack(void);

	const Unit* GetUnit() const;
	int GetAmount() const;

	void Attack( Stack& victim );
	void OnDamage( int iDamage );

private:
	const Unit* m_pUnit;

	int m_iAmount;
	int m_iHealth;
};

