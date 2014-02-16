#include "Talent.h"


Talent::Talent(void)
{
}


Talent::~Talent(void)
{
}

const HashedString& Talent::GetName() const
{
	return m_hName;
}

void Talent::SetName( HashedString& hName )
{
	m_hName = hName;
}

void Talent::SetIcon( const std::string& strIconFilename )
{
	m_strIcon = strIconFilename;
}

const std::string& Talent::GetIcon() const
{
	return m_strIcon;
}

void Talent::SetDescription( const std::string& strDescription )
{
	m_strDescription = strDescription;
}

const std::string& Talent::GetDescription() const
{
	return m_strDescription;
}
