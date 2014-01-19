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
#include "Processes/MainMenuProcess.h"

using namespace Engine;

void Start()
{
#ifdef _WIN32
	FolderAssetBundle* pAssetsBundle = new FolderAssetBundle( FileUtils::GetWorkingFolder() + "../Assets/");
	AssetManager::Get().AddAssetBundle( pAssetsBundle );
#endif
    FolderAssetBundle* pBundle = new FolderAssetBundle( FileUtils::GetWorkingFolder() );
    AssetManager::Get().AddAssetBundle( pBundle );
    
	MainMenuProcess* pMainMenu = new MainMenuProcess();
	BaseApplication::Get()->AttachProcess( pMainMenu );
	pMainMenu->Release();
}

void Update( float fDeltaSeconds )
{
    
    
}

void End()
{
    
}