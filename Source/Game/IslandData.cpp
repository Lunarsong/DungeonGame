    //
//  IslandData.cpp
//  VillageGame
//
//  Created by Shanee on 9/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "IslandData.h"
#include <stdio.h>
#include "Core/Math/RandomNumGen.h"
#include <vector>
#include <ctime>
#include <Core/Utils/Macros.h>
#include <Core/Math/Vector3.h>

IslandData::IslandData()
{
    m_pHeightMap		= NULL;
    m_pHeightMaskMap	= NULL;
	m_pBiomeMap			= NULL;
	m_pMoistureMap		= NULL;
        
    m_uiSizeX = 0;
    m_uiSizeY = 0;
}
    
IslandData::~IslandData()
{
    Destroy();
}
    
void IslandData::Destroy()
{
    if ( m_pHeightMap )
    {
        delete []  m_pHeightMap;
		m_pHeightMap = NULL;
    }
        
    if ( m_pHeightMaskMap )
    {
        delete [] m_pHeightMaskMap;
		m_pHeightMaskMap = NULL;
    }

	if ( m_pBiomeMap )
	{
		delete [] m_pBiomeMap;
		m_pBiomeMap = NULL;
	}

	SAFE_DELETE_ARRAY( m_pMoistureMap );
}
    
void IslandData::Generate( int iWidth, int iHeight )
{
    Destroy();
        
    m_uiSizeY = iHeight;
    m_uiSizeX = iWidth;
        
    m_pHeightMap = new float[ iHeight * iWidth ];
    Engine::SimplexNoise noise;
    noise.SetOctaves( 16.0f );
    noise.SetPersistence( 0.5f );
    noise.SetScale( 0.005f );
    noise.SetBounds( -0.25f, 1.0f );
        
    for ( unsigned int y = 0; y < iHeight; ++y )
    {
        for ( unsigned int x = 0; x < iWidth; ++x )
        {
            (*this)( x ,  y ) = noise.Noise( x, y );
        }
    }
        
    GenerateMaskMap();

    for ( unsigned int y = 0; y < iHeight; ++y )
    {
        for ( unsigned int x = 0; x < iWidth; ++x )
        {
            (*this)( x ,  y ) = std::min( m_pHeightMap[ y * m_uiSizeX + x ] * GetMaskHeight( x, y ), 1.0f );
        }
    }
        
}
    
void IslandData::Generate( int iWidth, int iHeight, unsigned long ulSeed )
{
    Destroy();
        
    m_pHeightMap = new float[ iHeight * iWidth ];
}
    
enum IslandDataMaskMapDirection
{
    Up,
    Down,
    Left,
    Right
};
    
void IslandData::GenerateMaskMap()
{
	/*
	var perlin:BitmapData = new BitmapData(256, 256);
	perlin.perlinNoise(64, 64, 8, seed, false, true);

	return function (q:Point):Boolean {
	var c:Number = (perlin.getPixel(int((q.x+1)*128), int((q.y+1)*128)) & 0xff) / 255.0;
	return c > (0.3+0.3*q.length*q.length);

	*/
    m_pHeightMaskMap = new float[ m_uiSizeX * m_uiSizeY ];     

	Engine::SimplexNoise noise;
	noise.SetOctaves( 8.0f );
	noise.SetPersistence( 0.5f );
	noise.SetScale( 0.015f );
	noise.SetBounds( 0.0, 1.0f );

    for ( unsigned int y = 0; y < m_uiSizeY; ++y )
    {
        for ( unsigned int x = 0; x < m_uiSizeX; ++x )
        {
			Engine::Vector3 vPosition( x-m_uiSizeX*0.5, y-m_uiSizeY*0.5, 0.0f );
            float fDistance = ( 0.3f + 0.3f * vPosition.LengthSQ() );
            
			float fNoise = noise.Noise( x, y );
            float fModifiedNoise = fNoise*m_uiSizeX*5;
            if ( fModifiedNoise < fDistance )
            {
                fNoise = ( fModifiedNoise / fDistance - 0.1f ) * 5.0f;
                if ( fNoise > 1.0f )
                {
                    fNoise = 1.0f;
                }
            }
            
            else
            {
                fNoise = 1.0f;
            }
            
            m_pHeightMaskMap[ y * m_uiSizeY + x ] = fNoise;
        }
    }

	return;

	m_pHeightMaskMap = new float[ m_uiSizeX * m_uiSizeY ];        
	for ( unsigned int y = 0; y < m_uiSizeY; ++y )
	{
		for ( unsigned int x = 0; x < m_uiSizeX; ++x )
		{
			m_pHeightMaskMap[ y * m_uiSizeY + x ] = 0.0f;
		}
	}
        
    Engine::RandomNumGen rand;
    rand.SetRandomSeed( time( NULL ) );
        
    std::vector< IslandDataMaskMapDirection > choices;
    choices.reserve( 4 );
    int iNumIterations0 = m_uiSizeX * m_uiSizeY * 0.85f;
    int iNumIterations1 = m_uiSizeX * m_uiSizeY * 0.05f;
    for ( int i = 0; i < iNumIterations0; ++i )
    {
        int x = rand.RandomInt( 15, m_uiSizeX - 16 );
        int y = rand.RandomInt( 15, m_uiSizeY - 16 );
            
        for ( int j = 0; j < iNumIterations1; ++j )
        {
            choices.clear();
            m_pHeightMaskMap[ y * m_uiSizeY + x ] += 7.0f;
            if ( m_pHeightMaskMap[ y * m_uiSizeY + x ] > 255.0f )
            {
                m_pHeightMaskMap[ y * m_uiSizeY + x ] = 255.0f;
            }
                
            float fCurrentValue = m_pHeightMaskMap[ y * m_uiSizeY + x ];
                
            if ( ( x - 1 ) > 0 )
            {
                if ( m_pHeightMaskMap[ y * m_uiSizeY + x-1 ] <= fCurrentValue )
                    choices.push_back( Left );
            }
                
            if ( ( x + 1 ) < ( m_uiSizeX - 1 ) )
            {
                if ( m_pHeightMaskMap[ y * m_uiSizeY + x+1 ] <= fCurrentValue )
                    choices.push_back( Right );
            }


            if ( ( y - 1 ) > 0 )
            {
                if ( m_pHeightMaskMap[ (y-1) * m_uiSizeY + x ] <= fCurrentValue )
                    choices.push_back( Down );
            }

                
            if ( ( y + 1 ) < ( m_uiSizeY - 1 ) )
            {
                if ( m_pHeightMaskMap[ (y+1) * m_uiSizeY + x ] <= fCurrentValue )
                    choices.push_back( Up );
            }

            if ( choices.size() == 0 )
                break;
                
            IslandDataMaskMapDirection eDirection = choices[ rand.RandomInt( choices.size() ) ];
            switch ( eDirection )
            {
                case Left:
                    x -= 1;
                    break;
                        
                case Right:
                    x += 1;
                    break;
                        
                case Up:
                    y += 1;
                    break;
                        
                case Down:
                    y -= 1;
                    break;
            }

                
        }
    }

    /*
        for i in range(0, int((width*height)*(.85))):
        x = random.randint(15, self.map_width-16)
        y = random.randint(15, self.map_height-16)
         
        for j in range(0, int((width*height)*(0.05))):
        particle_map[y][x] += 7
        if particle_map[y][x] >= 255:
        particle_map[y][x] == 255
        current_value = particle_map[y][x]
        choices = []
        if x-1 > 0:
        if particle_map[y][x-1] <= current_value:
        choices.append("left")
        if x+1 < self.map_width-1:
        if particle_map[y][x+1] <= current_value:
        choices.append("right")
        if y-1 > 0:
        if particle_map[y-1][x] <= current_value:
        choices.append("up")
        if y+1 < self.map_height-1:
        if particle_map[y+1][x] <= current_value:
        choices.append("down")
         
        if not choices:
        break;
         
        new = random.choice(choices)
        if new == "left":
        x -= 1
        elif new == "right":
        x += 1
        elif new == "up":
        y -= 1
        elif new == "down":
        y += 1
        */
        
}
    
float IslandData::GetHeight( int iX, int iY )
{
    return m_pHeightMap[ iY * m_uiSizeX + iX ];
}
    
float IslandData::GetMaskHeight( int iX, int iY )
{
	float fMask = m_pHeightMaskMap[ iY * m_uiSizeX + iX ];

	if ( fMask <= 0.0f )
		return 0.0f;

    return fMask;//( fMask / 255.0f - 0.5f ) * 2.0f;
}
    
inline
float& IslandData::operator() ( unsigned int iX, unsigned int iY )
{
    return m_pHeightMap[ iY * m_uiSizeX + iX ];
}

void IslandData::SetHeight( int iX, int iY, float fHeight )
{
	m_pHeightMap[ iY * m_uiSizeX + iX ] = fHeight;
}

void IslandData::GenerateBiomes()
{
	SAFE_DELETE_ARRAY( m_pBiomeMap );
	
	unsigned int uiNumTiles = m_uiSizeX * m_uiSizeY;
	m_pBiomeMap = new Biome[ uiNumTiles ];
	for ( unsigned int i = 0; i < uiNumTiles; ++i )
	{
		m_pBiomeMap[ i ] = Unassigned;
	}

	m_pBiomeMap[ 0 ] = SeaWater;
	m_pBiomeMap[ uiNumTiles - 1 ] = SeaWater;
	m_pBiomeMap[ m_uiSizeX - 1 ] = SeaWater;
	m_pBiomeMap[ ( m_uiSizeY - 1 ) * m_uiSizeX ] = SeaWater;
	for ( unsigned int y = 0; y < m_uiSizeY; ++y )
	{
		for ( unsigned int x = 0; x < m_uiSizeX; ++x )
		{
			SeaForm( x, y );
			SeaForm( x, m_uiSizeY - y - 1 );
			SeaForm( m_uiSizeX - x - 1, y );

			SeaForm( m_uiSizeX - x - 1, m_uiSizeY - y - 1 );
		}
	}

	for ( unsigned int y = 0; y < m_uiSizeY; ++y )
	{
		for ( unsigned int x = 0; x < m_uiSizeX; ++x )
		{
			SeaForm( x, y );
			SeaForm( x, m_uiSizeY - y - 1 );
			SeaForm( m_uiSizeX - x - 1, y );

			SeaForm( m_uiSizeX - x - 1, m_uiSizeY - y - 1 );
		}
	}
	

	AssignLandOrFreshwater();

	GenerateMoisture();

}

void IslandData::SeaFormRecursive( unsigned int iX, unsigned int iY )
{
	if ( GetBiome( iX, iY ) != Unassigned )
	{
		return;
	}

	if ( GetHeight( iX, iY ) > 0.0f )
	{
		m_pBiomeMap[ iY * m_uiSizeX + iX ] = Land;
		return;
	}

	m_pBiomeMap[ iY * m_uiSizeX + iX ] = SeaWater;

	if ( iX > 1 )
	{
		SeaForm( iX - 1, iY );

		if ( iY > 1 )
		{
			SeaForm( iX - 1, iY - 1);
		}

		if ( iY < ( m_uiSizeY - 1 ) )
		{
			SeaForm( iX - 1, iY + 1 );
		}
	}

	if ( iX < ( m_uiSizeX - 1 ) )
	{
		SeaForm( iX + 1, iY );

		if ( iY > 1 )
		{
			SeaForm( iX + 1, iY - 1);
		}

		if ( iY < ( m_uiSizeY - 1 ) )
		{
			SeaForm( iX + 1, iY + 1 );
		}
	}

	if ( iY > 1 )
	{
		SeaForm( iX, iY - 1);
	}

	if ( iY < ( m_uiSizeY - 1 ) )
	{
		SeaForm( iX, iY + 1 );
	}
}

void IslandData::SeaForm( unsigned int iX, unsigned int iY )
{
	/*if ( GetBiome( iX, iY ) != Unassigned )
	{
		return;
	}*/

	if ( GetHeight( iX, iY ) > 0.0f )
	{
		m_pBiomeMap[ iY * m_uiSizeX + iX ] = Land;
		return;
	}

	if ( m_pBiomeMap[ iY * m_uiSizeX + iX ] != SeaWater )
	{
		return;
	}

	if ( iX > 1 )
	{
		if ( GetHeight( iX - 1, iY ) <= 0.0f )
		{
			m_pBiomeMap[ iY * m_uiSizeX + iX - 1 ] = SeaWater;
		}

		if ( iY > 1 )
		{
			if ( GetHeight( iX - 1, iY - 1 ) <= 0.0f )
			{
				m_pBiomeMap[ (iY-1) * m_uiSizeX + iX - 1 ] = SeaWater;
			}
		}

		if ( iY < ( m_uiSizeY - 1 ) )
		{
			if ( GetHeight( iX - 1, iY + 1 ) <= 0.0f )
			{
				m_pBiomeMap[ (iY+1) * m_uiSizeX + iX - 1 ] = SeaWater;
			}
		}
	}

	if ( iX < ( m_uiSizeX - 1 ) )
	{
		if ( GetHeight( iX  + 1, iY ) <= 0.0f )
		{
			m_pBiomeMap[ iY * m_uiSizeX + iX + 1 ] = SeaWater;
		}

		if ( iY > 1 )
		{
			if ( GetHeight( iX  + 1, iY - 1 ) <= 0.0f )
			{
				m_pBiomeMap[ (iY-1) * m_uiSizeX + iX + 1 ] = SeaWater;
			}
		}

		if ( iY < ( m_uiSizeY - 1 ) )
		{
			if ( GetHeight( iX  + 1, iY + 1 ) <= 0.0f )
			{
				m_pBiomeMap[ (iY+1) * m_uiSizeX + iX + 1 ] = SeaWater;
			}
		}
	}

	if ( iY > 1 )
	{
		if ( GetHeight( iX , iY-1 ) < 0.0f )
		{
			m_pBiomeMap[ (iY-1) * m_uiSizeX + iX ] = SeaWater;
		}
	}

	if ( iY < ( m_uiSizeY - 1 ) )
	{
		if ( GetHeight( iX, iY + 1 ) < 0.0f )
		{
			m_pBiomeMap[ (iY+1) * m_uiSizeX + iX ] = SeaWater;
		}
	}
}

IslandData::Biome IslandData::GetBiome( unsigned int iX, unsigned int iY ) const
{
	return m_pBiomeMap[ iY * m_uiSizeX + iX ];
}

void IslandData::AssignLandOrFreshwater()
{
	for ( unsigned int iY = 0; iY < m_uiSizeY; ++iY )
	{
		for ( unsigned int iX = 0; iX < m_uiSizeX; ++iX )
		{
			if ( GetBiome( iX, iY ) == Unassigned )
			{
				if ( GetHeight( iX, iY ) > 0.0f )
				{
					m_pBiomeMap[ iY * m_uiSizeX + iX ] = Land;
				}

				else
				{
					m_pBiomeMap[ iY * m_uiSizeX + iX ] = FreshWater;
				}
				
			}
		}
	}
	
}
 
float IslandData::GetMoisture( unsigned int iX, unsigned int iY ) const
{
	return m_pMoistureMap[ iY * m_uiSizeX + iX ];
}

void IslandData::GenerateMoisture()
{
	SAFE_DELETE_ARRAY( m_pMoistureMap );
	
	Engine::SimplexNoise noise;
	noise.SetOctaves( 16.0f );
	noise.SetPersistence( 0.5f );
	noise.SetScale( 0.005f );
	noise.SetBounds( -0.1f, 1.2f );

	m_pMoistureMap = new float[ m_uiSizeX * m_uiSizeY ];
	for ( unsigned int iY = 0; iY < m_uiSizeY; ++iY )
	{
		for ( unsigned int iX = 0; iX < m_uiSizeX; ++iX )
		{
			Biome eBiome = GetBiome( iX, iY );
			if ( eBiome == FreshWater )
			{
				m_pMoistureMap[ iY * m_uiSizeX + iX ] = 1.0f;
			}

			else if ( eBiome == SeaWater )
			{
				m_pMoistureMap[ iY * m_uiSizeX + iX ] = 0.0f;
			}

			else
			{
				m_pMoistureMap[ iY * m_uiSizeX + iX ] = std::min( std::max( 0.0f, noise.Noise( iX, iY ) * GetMaskHeight( iX, iY ) * 1.7f ), 1.0f );
			}
		}
	}

	for ( unsigned int iY = 0; iY < m_uiSizeY; ++iY )
	{
		for ( unsigned int iX = 0; iX < m_uiSizeX; ++iX )
		{
			Biome eBiome = GetBiome( iX, iY );
			if ( eBiome == FreshWater || eBiome == SeaWater )
			{
				DistributeMoisture( iX, iY );
			}
		}
	}

	for ( unsigned int iY = 0; iY < m_uiSizeY; ++iY )
	{
		for ( unsigned int iX = 0; iX < m_uiSizeX; ++iX )
		{
			Biome eBiome = GetBiome( iX, iY );
			if ( eBiome == SeaWater )
			{
				m_pMoistureMap[ iY * m_uiSizeX + iX ] = 1.0f;
			}
		}
	}

	Biome eBiomeMap[4][6];
	eBiomeMap[0][0] = SubtropicalDesert;
	eBiomeMap[0][1] = Grassland;
	eBiomeMap[0][2] = TropicalSeasonalForest;
	eBiomeMap[0][3] = TropicalSeasonalForest;
	eBiomeMap[0][4] = TropicalRainForest;
	eBiomeMap[0][5] = TropicalRainForest;

	eBiomeMap[1][0] = TemperateDesert;
	eBiomeMap[1][1] = Grassland;
	eBiomeMap[1][2] = Grassland;
	eBiomeMap[1][3] = TemperateDecidousForest;
	eBiomeMap[1][4] = TemperateDecidousForest;
	eBiomeMap[1][5] = TemperateRainForest;

	eBiomeMap[2][0] = TemperateDesert;
	eBiomeMap[2][1] = TemperateDesert;
	eBiomeMap[2][2] = Shrubland;
	eBiomeMap[2][3] = Shrubland;
	eBiomeMap[2][4] = Taiga;
	eBiomeMap[2][5] = Taiga;

	eBiomeMap[3][0] = Scorched;
	eBiomeMap[3][1] = Bare;
	eBiomeMap[3][2] = Tundra;
	eBiomeMap[3][3] = Snow;
	eBiomeMap[3][4] = Snow;
	eBiomeMap[3][5] = Snow;

	for ( unsigned int iY = 0; iY < m_uiSizeY; ++iY )
	{
		for ( unsigned int iX = 0; iX < m_uiSizeX; ++iX )
		{
			Biome eBiome = GetBiome( iX, iY );
			if ( eBiome == Land )
			{
				float fMoisture = GetMoisture( iX, iY );
				float fHeight = GetHeight( iX, iY );

				int iHeightIndex = (int)(fHeight * 4.8f);
				int iMoistureIndex = (int)(fMoisture * 5.2);

				m_pBiomeMap[ iY * m_uiSizeX + iX ] = eBiomeMap[iHeightIndex][iMoistureIndex];

                if ( iMoistureIndex >= 5 || iHeightIndex > 3 )
                {
                    iMoistureIndex = 5;
                    iHeightIndex = 3;
                }
			}
		}
	}

}

void IslandData::DistributeMoisture( unsigned int iX, unsigned int iY )
{
	float fAltitude = GetHeight( iX, iY );
	float fMoisture = GetMoisture( iX, iY );

	static const float k_fDiagonalFalloff = 0.925f;
	if ( iX > 1 )
	{
		RecieveMoisture( fMoisture, fAltitude, iX - 1, iY );

		if ( iY > 1 )
		{
			RecieveMoisture( fMoisture * k_fDiagonalFalloff, fAltitude, iX - 1, iY - 1 );
		}

		if ( iY < ( m_uiSizeY - 1 ) )
		{
			RecieveMoisture( fMoisture * k_fDiagonalFalloff, fAltitude, iX - 1, iY + 1 );
		}
	}

	if ( iX < ( m_uiSizeX - 1 ) )
	{
		RecieveMoisture( fMoisture, fAltitude, iX + 1, iY );

		if ( iY > 1 )
		{
			RecieveMoisture( fMoisture * k_fDiagonalFalloff, fAltitude, iX + 1, iY - 1 );
		}

		if ( iY < ( m_uiSizeY - 1 ) )
		{
			RecieveMoisture( fMoisture * k_fDiagonalFalloff, fAltitude, iX + 1, iY + 1 );
		}
	}

	if ( iY > 1 )
	{
		RecieveMoisture( fMoisture, fAltitude, iX, iY - 1 );
	}

	if ( iY < ( m_uiSizeY - 1 ) )
	{
		RecieveMoisture( fMoisture, fAltitude, iX, iY + 1 );
	}
}

void IslandData::RecieveMoisture( float fMoisture, float fAltitude, unsigned int iX, unsigned int iY )
{
	float fMyMoisture = GetMoisture( iX, iY );
	//float fMyHeight = GetHeight( iX, iY );

	if ( fMoisture > fMyMoisture )
	{
		/*if ( fAltitude > fMyHeight )
		{
			static const float k_fMoistureFalloff = 0.85f;
			fMoisture *= k_fMoistureFalloff;
		}

		else*/
		{
			static const float k_fMoistureFalloffFromLower = 0.85f;
			fMoisture *= k_fMoistureFalloffFromLower;
		}

		if ( fMoisture > fMyMoisture )
		{
			m_pMoistureMap[ iY * m_uiSizeX + iX ] = fMoisture;

			if ( fMoisture > 0.1f )
			DistributeMoisture( iX, iY );
		}
	}
}
