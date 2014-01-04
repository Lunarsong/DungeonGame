//
//  GameMap.cpp
//  DungeonGame
//
//  Created by Shanee on 12/26/13.
//
//

#include "GameMap.h"

GameMap::GameMap()
{
    m_pMap = NULL;
    m_iSizeX = 0;
    m_iSizeY = 0;
}

GameMap::~GameMap()
{
    Destroy();
}

void GameMap::Destroy()
{
    if ( m_pMap )
    {
        delete [] m_pMap;
        m_pMap = NULL;
    }
    
    m_iSizeX = 0;
    m_iSizeY = 0;
}

int GameMap::GetSizeX() const
{
    return m_iSizeX;
}

int GameMap::GetSizeY() const
{
    return m_iSizeY;
}

bool GameMap::Create( const BinaryResource* pResource )
{
    Destroy();
    
    if ( CreateFromAscii( pResource ) )
        return true;
    
    return false;
}

bool GameMap::CreateFromAscii( const BinaryResource* pResource )
{
    const char* pBuffer = pResource->Buffer();
    unsigned int uiSize = pResource->BlobSize();
    
    bool bSuccess = false;
    for ( unsigned int i = 0; i < uiSize; ++i )
    {
        if ( pBuffer[ i ] == '\n' )
        {
            m_iSizeX = i;
            m_iSizeY = i;
            
            bSuccess = true;
            
            break;
        }
    }
    
    if ( !bSuccess )
    {
        return false;
    }
    
    bSuccess = false;
    m_pMap = new char[ m_iSizeY * m_iSizeX ];
    
    
    unsigned int iTilePos = 0;
    unsigned int iX = 0;
    for ( unsigned int i = 0; i < uiSize; ++i )
    {
        // Reach end of line
        if ( iX == m_iSizeX )
        {
            if ( pBuffer[ i ] != '\n' )
            {
                throw "Expected endline";
            }
            
            else
            {
                iX = 0;
                continue;
            }
        }
        
        if ( pBuffer[ i ] == '\n' )
            throw "Unexpected newline";
        
        ++iX;
        m_pMap[ iTilePos++ ] = pBuffer[ i ];
    }
    
    return true;;
}

char& GameMap::operator() ( unsigned int iX, unsigned int iY )
{
    assert( iX < m_iSizeX && iY < m_iSizeY && m_pMap );
    
    return m_pMap[ m_iSizeX * iY + iX ];
}

const char& GameMap::operator() ( unsigned int iX, unsigned int iY ) const
{
    assert( iX < m_iSizeX && iY < m_iSizeY && m_pMap );
    
    return m_pMap[ m_iSizeX * iY + iX ];
}