#pragma once

#include <string>

class Hero
{
public:
	Hero(void);
	~Hero(void);

	const std::string& GetName() const { return m_Name; }

	int GetStepsRemains() const { return m_iStepsRemains; }
	int GetMovement() const { return m_iMovement; }

	int GetMagic() const { return m_iMagic; }
	int GetPower() const { return m_iPower; }

	int GetMagicDefense() const { return m_iMagicDefense; }
	int GetArmor() const { return m_iArmor; }

	int GetMorale() const { return m_iMorale; }
	int GetLuck() const { return m_iLuck; }

	int GetManaMax() const { return 0; }
	int GetMana() const { return 0; }

private:
	std::string m_Name;

	int m_iMovement;
	int m_iStepsRemains;

	int m_iMagic;
	int m_iPower;

	int m_iMagicDefense;
	int m_iArmor;

	int m_iMorale;
	int m_iLuck;
};

