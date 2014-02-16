#include "CaveGeneator.h"
#include <assert.h>


CaveGeneator::CaveGeneator(void)
{
	m_iFillProbability = 40;
	m_iSizeX = 64;
	m_iSizeY = 20;

	m_pGrid = NULL;
	m_pGrid2 = NULL;
}


CaveGeneator::~CaveGeneator(void)
{
	Destroy();
}

void CaveGeneator::Generate( unsigned long ulSeed, int iSizeX, int iSizeY, int iGenerations /*= 3*/, int iFillProbability /*= 40 */ )
{
	m_iSizeX			= iSizeX;
	m_iSizeY			= iSizeY;
	m_iFillProbability  = iFillProbability;

	Engine::g_RandomNumGen.SetRandomSeed( ulSeed );
	InitMap();

	int iCutOffR1 = 5;
	int iCutOffR2 = 2;
	for ( int i = 0; i < iGenerations; ++i )
	{
		if ( i > 3 )
		{
			iCutOffR1 = 5;
			iCutOffR2 = -1;
		}

		PlaceWalls( iCutOffR1, iCutOffR2 );
	}

	delete [] m_pGrid2;
	m_pGrid2 = NULL;
}

int& CaveGeneator::Grid( int x, int y )
{
	return m_pGrid[ y * m_iSizeX + x ];
}

int& CaveGeneator::Grid2( int x, int y )
{
	return m_pGrid2[ y * m_iSizeX + x ];
}

int CaveGeneator::RandomPick()
{
	unsigned int uiValue = Engine::g_RandomNumGen.RandomInt( 100 );
	if ( uiValue < m_iFillProbability )
	{
		return TILE_WALL;
	}

	else
	{
		return TILE_FLOOR;
	}
}

void CaveGeneator::InitMap( void )
{
	m_pGrid = new int[ m_iSizeY * m_iSizeX ];
	m_pGrid2 = new int[ m_iSizeY * m_iSizeX ];

	for ( int y = 1; y < m_iSizeY-1; ++y )
	{
		for ( int x = 1; x < m_iSizeX-1; ++x )
		{
			Grid( x, y ) = RandomPick();
		}
	}

	for ( int y = 0; y < m_iSizeY; ++y )
	{
		for ( int x = 0; x < m_iSizeX; ++x )
		{
			Grid2( x, y ) = TILE_WALL;
		}
	}

	for ( int y = 0; y < m_iSizeY; ++y )
	{
		Grid( 0, y ) = TILE_WALL;
		Grid( m_iSizeX-1, y ) = TILE_WALL;
	}

	for ( int x = 0; x < m_iSizeX; ++x )
	{
		Grid( x, 0 ) = TILE_WALL;
		Grid( x, m_iSizeY-1 ) = TILE_WALL;
	}
}

void CaveGeneator::PlaceWalls( int iCutOff1 /*= 5*/, int iCutOff2 /*= 2 */ )
{
	for ( int y = 1; y < m_iSizeY-1; ++y )
	{
		for ( int x = 1; x < m_iSizeX-1; ++x )
		{
			int adjcount_r1 = 0;
			int adjcount_r2 = 0;

			for ( int i = -1; i <= 1; ++i )
			{
				for ( int j = -1; j <= 1; ++j )
				{
					if ( Grid( x + j, y + i ) != TILE_FLOOR )
					{
						++adjcount_r1;
					}
				}
			}

			for ( int i = (y-2); i <= (y+2); ++i )
			{
				for ( int j = (x-2); j <= (x+2); ++j )
				{
					if ( abs( i-y ) == 2 && abs( j - x ) == 2 )
						continue;

					if ( i < 0 || j < 0 || i >= m_iSizeY || j >= m_iSizeX )
						continue;

					if ( Grid( j, i ) != TILE_FLOOR )
						++adjcount_r2;
				}
			}

			if ( adjcount_r1 >= iCutOff1 || adjcount_r2 <= iCutOff2 )
				Grid2( x, y ) = TILE_WALL;

			else
				Grid2( x, y ) = TILE_FLOOR;
		}
	}

	for ( int y = 1; y < m_iSizeY-1; ++y )
	{
		for ( int x = 1; x < m_iSizeX-1; ++x )
		{
			Grid( x, y ) = Grid2( x, y );
		}
	}
}

void CaveGeneator::Destroy()
{
	m_iSizeX = 0;
	m_iSizeY = 0;

	if ( m_pGrid )
	{
		delete [] m_pGrid;
		m_pGrid = NULL;
	}

	if ( m_pGrid2 )
	{
		delete [] m_pGrid2;
		m_pGrid2 = NULL;
	}
}

int& CaveGeneator::operator()( unsigned int iX, unsigned int iY )
{
	assert( m_pGrid && ( iY * m_iSizeX + iX ) < ( m_iSizeX * m_iSizeY ) );

	return m_pGrid[ iY * m_iSizeX + iX ];
}

const int& CaveGeneator::operator()( unsigned int iX, unsigned int iY ) const
{
	assert( m_pGrid && ( iY * m_iSizeX + iX ) < ( m_iSizeX * m_iSizeY ) );

	return m_pGrid[ iY * m_iSizeX + iX ];
}
