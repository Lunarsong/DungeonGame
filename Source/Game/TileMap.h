#pragma once

#include "Tile.h"
#include <vector>
#include <Core/Utils/Array2D.h>
#include <Game/Entities/Entity.h>
#include <list>

struct TileData
{
	const Tile* mTile;
	std::list< Engine::Entity* > mEntities;

	TileData()
	{
		//mTile = NULL;
		
	}

	void RemoveEntity( Engine::Entity* pEntity )
	{
		mEntities.remove( pEntity );
	}

	void AddEntity( Engine::Entity* pEntity )
	{
		mEntities.push_back( pEntity );
	}
};

class TileMap : public Engine::Array2D< TileData >
{
public:
	TileMap(void);
	~TileMap(void);


private:

};

