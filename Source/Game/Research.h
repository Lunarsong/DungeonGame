#pragma once

#include "Economy.h"

class Knowledge : public Producible
{
public:
	Knowledge();
	~Knowledge();
};

class Research
{
public:
	Research(void);
	~Research(void);

	void SetCurrentResearch( const HashedString& hResearch );
	void Progress( int iAmount );

private:
	std::map< HashedString, int > m_ResearchProgress;
};