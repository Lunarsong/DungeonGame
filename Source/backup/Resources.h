#pragma once

class Resource
{
public:
	Resource(void);
	~Resource(void);

	enum Resources
	{
		Gold = 0,
		Wood,
		Stone,
		Crystals,		

		ResourcesCount
	};

	int GetAmount() const;

	int GetIncome() const;


private:
	Resources	m_eType;
	int			m_iAmount;
	int			m_iIncome;
};

