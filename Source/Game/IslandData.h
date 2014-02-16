//
//  IslandData.h
//  VillageGame
//
//  Created by Shanee on 9/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <Core/Utils/SimplexNoise.h>

class IslandData
{
public:
	enum Biome
	{
		Unassigned = 0,
		SeaWater,
		FreshWater,
		Land,

		Snow,
		Tundra,
		Bare,
		Scorched,
		Taiga,
		Shrubland,
		TemperateDesert,

		TemperateRainForest,
		TemperateDecidousForest,
		Grassland,
		//TemperateDesert
		
		TropicalRainForest,
		TropicalSeasonalForest,
		//Grassland,
		SubtropicalDesert,

		BiomeCount
	};

    IslandData();
    ~IslandData();

    void Destroy();

    void Generate( int iWidth, int iHeight );
    void Generate( int iWidth, int iHeight, unsigned long ulSeed );

	void GenerateBiomes();

    float GetHeight( int iX, int iY );
	void SetHeight( int iX, int iY, float fHeight );
    float GetMaskHeight( int iX, int iY );

	Biome GetBiome( unsigned int iX, unsigned int iY ) const;
	float GetMoisture( unsigned int iX, unsigned int iY ) const;
    
    // casting operators
    operator float* () { return m_pHeightMap; }
    operator const float* () const { return m_pHeightMap; }

private:
    float* m_pHeightMap;
    float* m_pHeightMaskMap;
	float* m_pMoistureMap;
	Biome* m_pBiomeMap;
        
    unsigned int m_uiSizeX, m_uiSizeY;

    inline float& operator() ( unsigned int iX, unsigned int iY );
        
    void GenerateMaskMap();

	void SeaForm( unsigned int iX, unsigned int iY );
	void SeaFormRecursive( unsigned int iX, unsigned int iY );
	
	void DistributeMoisture( unsigned int iX, unsigned int iY );
	void RecieveMoisture( float fMoisture, float fAltitude, unsigned int iX, unsigned int iY );

	void AssignLandOrFreshwater();

	void GenerateMoisture();
};