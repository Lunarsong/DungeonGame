#pragma once

#include <Externals/HashedString/HashedString.h>
#include <list>
#include <string>
#include "Attribute.h"

//using namespace Engine;

class Talent
{
public:
	Talent(void);
	~Talent(void);

	const HashedString& GetName() const;
	void SetName( HashedString& hName );

	void SetIcon( const std::string& strIconFilename );
	const std::string& GetIcon() const;

	void SetDescription( const std::string& strDescription );
	const std::string& GetDescription() const;

	struct Cost
	{
		Attributes	eAttribute;
		int			iCost;
	};

	struct Prerequisite
	{
		enum Type
		{
			Attribute,
			Level,
			Talent
		};

		Type eType;
		HashedString hTalentName;
		Attributes eAttribute;
		int iAttributeValue;
	};

private:
	HashedString	m_hName;
	std::string		m_strIcon;
	std::string		m_strDescription;

	std::list< Cost >			m_Costs;
	std::list< Prerequisite >	m_Prerequisites;
	

};

