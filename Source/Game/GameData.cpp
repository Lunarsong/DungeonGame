#include "GameData.h"
#include <Game/Entities/Component.h>
#include "Faction/City.h"
#include <Core/Resources/XmlResource.h>

using namespace  Engine;

GameData::GameData(void)
{
	Engine::Component::Register<City>();
	Engine::Component::Register<Producible>();
	Engine::Component::Register<Unit>();
}


GameData::~GameData(void)
{
	for ( auto it : mEntities )
	{
		it.second->Release();
	}
}

void GameData::AddUnit( Unit* pUnit )
{
	//assert( GetUnit( pUnit->GetName() ) == NULL );

	//m_Units[ pUnit->GetName() ] = pUnit;
}

const Unit* GameData::GetUnit( const HashedString& hUnit ) const
{
	std::map< HashedString, Unit* >::const_iterator pIter = m_Units.find( hUnit );
	if ( pIter != m_Units.end() )
	{
		return pIter->second;
	}

	return NULL;
}

bool GameData::LoadFromFile( const char* pFilename )
{
	XmlResource* pResource = AssetManager::Get().GetAsset<XmlResource>( pFilename );
	if ( pResource && pResource->GetRoot() )
	{
		ParseXML( pResource->GetRoot() );

		return true;
	}	

	return false;
}

void GameData::Load( BinaryResource* pResource )
{

}

void GameData::AddBuilding( Building* pBuilding )
{
	assert( GetBuilding( pBuilding->mName ) == NULL );
	m_Buildings[ pBuilding->mName ] = pBuilding;
}

const Building* GameData::GetBuilding( const HashedString& hBuilding ) const
{
	std::map< HashedString, Building* >::const_iterator pIter = m_Buildings.find( hBuilding );
	if ( pIter != m_Buildings.end() )
	{
		return pIter->second;
	}

	return NULL;
}

void GameData::AddTile( Tile* pTile )
{
	assert( GetTile( pTile->mName ) == NULL );

	m_Tiles[ pTile->mName ] = pTile;
}

const Tile* GameData::GetTile( const HashedString& hTile ) const
{
	std::map< HashedString, Tile* >::const_iterator pIter = m_Tiles.find( hTile );
	if ( pIter != m_Tiles.end() )
	{
		return pIter->second;
	}

	return NULL;
}

void GameData::AddKnowledge( Knowledge* pKnowledge )
{
	/*assert( GetKnowledge( pKnowledge->mName ) == NULL );

	m_Knowledge[ pKnowledge->mName ] = pKnowledge;*/
}

const Knowledge* GameData::GetKnowledge( const HashedString& hKnowledge ) const
{
	std::map< HashedString, Knowledge* >::const_iterator pIter = m_Knowledge.find( hKnowledge );
	if ( pIter != m_Knowledge.end() )
	{
		return pIter->second;
	}

	return NULL;
}

void GameData::AddProducible( const HashedString& hProducible, Producible* pProducible )
{
	m_Producibles[ hProducible ] = pProducible;
}

const Producible* GameData::GetProducible( const HashedString& hProducible ) const
{
	std::map< HashedString, Producible* >::const_iterator pIter = m_Producibles.find( hProducible );
	if ( pIter != m_Producibles.end() )
	{
		return pIter->second;
	}

	return NULL;
}

const std::map< HashedString, Producible* >& GameData::GetProducibles() const
{
	return m_Producibles;
}

Entity* GameData::ParseEntity( tinyxml2::XMLElement* pElement )
{
	const char* pName = pElement->Attribute( "Name" );
	Entity* pEntity = new Entity();
	pEntity->SetName( pName );

	tinyxml2::XMLElement* pComponentElement = pElement->FirstChildElement();
	while ( pComponentElement )
	{
		Component* pComponent = Component::Instantiate( pComponentElement->Name() );

		if ( pComponent )
		{
			pComponent->VFromXML( pComponentElement );

			pEntity->AddComponent( pComponent );
			pComponent->Release();

			AddComponent( pEntity->GetName(), pComponent, pComponent->VGetType() );
		}		

		pComponentElement = pComponentElement->NextSiblingElement();
	}

	mEntities[ pName ] = pEntity;

	return pEntity;
}

void GameData::ParseXML( tinyxml2::XMLElement* pRoot )
{
	if ( pRoot )
	{
		tinyxml2::XMLElement* pEntityData = pRoot->FirstChildElement();
		while ( pEntityData )
		{
			if ( strcmp( pEntityData->Name(), "File" ) == 0 )
			{
				LoadFromFile( pEntityData->Attribute( "Path" ) );
			}

			else
			{
				ParseEntity( pEntityData );
			}
			

			pEntityData = pEntityData->NextSiblingElement();
		}
	}
}
void GameData::AddComponent( const HashedString& hName, Component* pComponent, const HashedString& hType )
{
	if ( hType == Producible::GetComponentType() )
	{
		m_Producibles[ hName ] = (Producible*)pComponent;
	}

	else if ( hType == City::GetComponentType() )
	{
		
	}
}

const Entity* GameData::GetEntity( const HashedString& hName ) const
{
	std::map< HashedString, Entity* >::const_iterator pIter = mEntities.find( hName );
	if ( pIter != mEntities.end() )
	{
		return pIter->second;
	}

	return NULL;
}
