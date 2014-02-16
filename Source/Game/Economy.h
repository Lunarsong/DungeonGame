#pragma once

#include <Externals/HashedString/HashedString.h>
#include <Core/Resources/ISerializable.h>
#include <map>
#include <Game/Entities/ComponentData.h>

class Economy
{
public:
	Economy(void);
	~Economy(void);


};

class Producible : public Engine::ComponentData
{
public:
	Producible();
	virtual ~Producible();

	AUTO_SIZE;
	SET_TYPE( Producible );

	unsigned short GetProductionTime() const { return m_usProductionTime; }

	const HashedString& GetIcon() const { return m_Icon; }

	const std::map< HashedString, int >& GetCost() const { return m_Cost; }
	const std::map< HashedString, int >& GetUpkeep() const { return m_Upkeep; }
	const std::map< HashedString, int >& GetPrerequisite() const { return m_Prerequisites; }

	virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
	virtual bool VFromXML( tinyxml2::XMLElement* pData );

	enum Type
	{
		Structure = 0,
		Unit,
		TypeCount
	};
	Type GetType() const { return m_eType; }

private:
	unsigned short m_usProductionTime;

	HashedString m_Icon;

	std::map< HashedString, int > m_Cost;
	std::map< HashedString, int > m_Upkeep;
	std::map< HashedString, int > m_Prerequisites;

	Type m_eType;
};

class Resource
{
public:
	Resource();
	~Resource();

	HashedString	mName;
	HashedString	mIcon;
};