#include "GameEntity.h"


GameEntity::GameEntity(void)
{
	m_pMap = NULL;
}


GameEntity::~GameEntity(void)
{
}

GameMap* GameEntity::GetMap()
{
	return m_pMap;
}

void GameEntity::SetMap( GameMap* pMap )
{
	m_pMap = pMap;
}

const Location& GameEntity::GetLocation() const
{
	return m_Location;
}

void GameEntity::SetLocation( unsigned int uiX, unsigned int uiY )
{
	m_Location.x = uiX; 
	m_Location.y = uiY;
}

unsigned int& GameEntity::Y()
{
	return m_Location.y;
}

unsigned int& GameEntity::X()
{
	return m_Location.x;
}

void GameEntity::UpdateMap()
{

}
