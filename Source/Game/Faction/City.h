#pragma once
#include <vector>
#include "Building.h"
#include "../Combat/Unit.h"
#include "Production.h"
#include <Game/Entities/Component.h>
#include <EntityData.h>
#include "../Economy.h"

class Faction;

class CityData : public Engine::ComponentData
{
public:
	CityData();
	~CityData();

	HashedString mRace;
	std::vector< HashedString > m_Buildings;

	virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;

	virtual bool VFromXML( tinyxml2::XMLElement* pData );

};

class City : public Engine::Component
{
public:
	City(void);
	~City(void);

	SET_TYPE( City );

	void Update();

	void SetName( const HashedString& hName );
	const HashedString& GetName() const;

	void SetFaction( Faction* pFaction );
	Faction* GetFaction();

	void Build( const HashedString& hName );
	void CancelBuild( Producible::Type eProductionType, int iIndex );

	void UpdateProducibles();

	const std::vector< const Engine::EntityData* >& GetProducibles() const { return m_Producibles; }

	bool VerifyPrerequisites( const Producible& producible ) const;

	void AdjustResource( const HashedString& hName, int iAmount );
	int GetResourceAmount( const HashedString& hName ) const;

private:
	// Owner Faction
	Faction*						m_Faction;

	// City Name
	HashedString					m_hName;

	// Produced & Producible
	std::vector< const Engine::EntityData* >	m_Producibles;
	std::map< HashedString, int >				m_Resources;
	/*std::vector< const Building* >	m_Buildings;
	std::vector< const Building* >	m_ProducibleBuildings;

	std::vector< const Unit* >		m_Units;
	std::vector< const Unit* >		m_ProducibleUnits;*/

	std::vector< Production >		m_Production[ Producible::TypeCount ];

	void UpdateProduction();
	void FinishProduction( const HashedString& hProduction, int iAmount );
	void StartProduction( const HashedString& hName );

};