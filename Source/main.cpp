//
//  main.c
//  DungeonGame
//
//  Created by Shanee on 12/25/13.
//
//

#include <stdio.h>
#include <Engine.h>
#include <Core/Utils/FileUtils.h>
#include "GameMap.h"
#include <Game/Entities/Components/Rendering/TileMapComponent.h>

using namespace Engine;

void Start()
{
    FolderAssetBundle* pBundle = new FolderAssetBundle( FileUtils::GetWorkingFolder() );
    AssetManager::Get().AddAssetBundle( pBundle );
    
    BinaryResource* pResource = AssetManager::Get().GetAsset< BinaryResource >( "Map.map" );
    GameMap map;
    map.Create( pResource );
    
    ITexture* pMapTexture = AssetManager::Get().GetAsset< ITexture >( "Tileset.png" );
    
    Entity* pMapEntity = Game::CreateEntity();
    TileMapComponent* pTileMap = new TileMapComponent( 10, 10, 32.0f, pMapTexture, [&] ( unsigned int x, unsigned int y, RectF& rect )
                                             {
                                                 char myChar = map( x, y );
                                                 myChar = myChar;
                                             }
                                             );
    
    pMapEntity->AddComponent( pTileMap );
    pTileMap->Start();
    pTileMap->Release();
    
}

void Update( float fDeltaSeconds )
{
    
}

void End()
{
    
}