#pragma once

class GameMap;

struct Location
{
	unsigned int x;
	unsigned int y;
};

class GameEntity
{
public:
	GameEntity(void);
	virtual ~GameEntity(void);

	GameMap* GetMap();
	void SetMap( GameMap* pMap );

	const Location& GetLocation() const;
	void SetLocation( unsigned int uiX, unsigned int uiY );
	unsigned int& X();
	unsigned int& Y();
	
	void UpdateMap();

private:
	GameMap* m_pMap;

	Location m_Location;
};