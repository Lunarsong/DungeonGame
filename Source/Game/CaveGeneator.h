#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Core/Math/RandomNumGen.h>

#define TILE_FLOOR 0
#define TILE_WALL 1

class CaveGeneator
{
public:
	CaveGeneator(void);
	~CaveGeneator(void);

	void Generate( unsigned long ulSeed, int iSizeX, int iSizeY, int iGenerations = 3, int iFillProbability = 40 );

	void Destroy();

	int& operator() ( unsigned int iX, unsigned int iY );
	const int& operator() ( unsigned int iX, unsigned int iY ) const;

private:
	int m_iSizeX;
	int m_iSizeY;

	int m_iFillProbability;

	int* m_pGrid;
	int* m_pGrid2;

	int& Grid( int x, int y );
	int& Grid2( int x, int y );

	int RandomPick();

	void InitMap(void);

	void PlaceWalls( int iCutOff1 = 5, int iCutOff2 = 2 ); 
};
