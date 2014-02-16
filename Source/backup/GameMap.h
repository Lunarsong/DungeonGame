//
//  GameMap.h
//  DungeonGame
//
//  Created by Shanee on 12/26/13.
//
//

#pragma once

#include <Core/Memory/IObject.h>
#include <list>

#include "GameEntity.h"

using namespace Engine;

class GameMap
{
    
public:
    GameMap();
    ~GameMap();
    
    void Destroy();
    
    bool Create( const BinaryResource* pResource );
    
    char& operator() ( unsigned int iX, unsigned int iY );
    const char& operator() ( unsigned int iX, unsigned int iY ) const;
    
    int GetSizeX() const;
    int GetSizeY() const;
    
    enum TileType
    {
        SideWall = '|',
        VerticalWall = '_',
        Water = '~',
        Block = '*',
        
        TileTypeCount
    };

	std::list< GameEntity* >& GetTileEntities( int uiX, int uiZ );

    
private:
    int m_iSizeX;
    int m_iSizeY;
    
    char* m_pMap;
    
    bool CreateFromAscii( const BinaryResource* pResource );

	struct TileData 
	{
		std::list< GameEntity* >	mEntities;
	};
	TileData* m_pTileMap;
};