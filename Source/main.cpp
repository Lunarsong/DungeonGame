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
#include "Skill.h"
#include "DungeonGame.h"

using namespace Engine;

void Start()
{
#ifdef _WIN32
	FolderAssetBundle* pAssetsBundle = new FolderAssetBundle( FileUtils::GetWorkingFolder() + "../Assets/");
	AssetManager::Get().AddAssetBundle( pAssetsBundle );
#endif
    FolderAssetBundle* pBundle = new FolderAssetBundle( FileUtils::GetWorkingFolder() );
    AssetManager::Get().AddAssetBundle( pBundle );
    
    DungeonGame* pDungeonGame = new DungeonGame();
    BaseApplication::Get()->AttachProcess( pDungeonGame );
    pDungeonGame->Release();
}

void Update( float fDeltaSeconds )
{
    Skill skill0;
    skill0.SetBase( 500 );
    
    Skill skill1;
    skill1.SetBase( 700 );
    
    Skill::Check( skill0, skill1 );
    
    
}

void End()
{
    
}