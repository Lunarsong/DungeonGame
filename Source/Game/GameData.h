#pragma once
#include <map>
#include "Combat/Unit.h"
#include <Externals/HashedString/HashedString.h>
#include <Core/AssetManager/AssetManager.h>
#include "Faction/Building.h"
#include "Tile.h"
#include "Research.h"
#include <EntityData.h>
#include <Game/Entities/Entity.h>

using namespace Engine;

class GameData : public Engine::Singleton< GameData >
{
public:
	GameData(void);
	~GameData(void);

	bool LoadFromFile( const char* pFilename );
	void ParseXML( tinyxml2::XMLElement* pRoot );

	void AddUnit( Unit* pUnit );
	const Unit* GetUnit( const HashedString& hUnit ) const;

	void AddBuilding( Building* pBuilding );
	const Building* GetBuilding( const HashedString& hBuilding ) const;

	void AddTile( Tile* pTile );
	const Tile* GetTile( const HashedString& hTile ) const;

	void AddKnowledge( Knowledge* pKnowledge );
	const Knowledge* GetKnowledge( const HashedString& hKnowledge ) const;

	void AddProducible( const HashedString& hProducible, Producible* pProducible );
	const Producible* GetProducible( const HashedString& hProducible ) const;

	const std::map< HashedString, Producible* >& GetProducibles() const;

	const Entity* GetEntity( const HashedString& hName ) const;

private:
	std::map< HashedString, Knowledge* >	m_Knowledge;
	std::map< HashedString, Unit* >			m_Units;
	std::map< HashedString, Building* >		m_Buildings;
	std::map< HashedString, Tile* >			m_Tiles;
	std::map< HashedString, Producible* >	m_Producibles;

	std::map< HashedString, Engine::Entity* > mEntities;
	void Load( BinaryResource* pResource );

	inline Entity* ParseEntity( tinyxml2::XMLElement* pElement );
	inline void AddComponent( const HashedString& hName, Component* pComponent, const HashedString& hType );
};