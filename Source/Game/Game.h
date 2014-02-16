#pragma once

#include "Faction/Faction.h"
#include <vector>
#include "IslandData.h"
#include "World.h"
#include "GameData.h"

class Game
{
public:
	Game(void);
	virtual ~Game(void);

	void Create( unsigned long ulSeed, unsigned int uiWorldSize );

	void EndTurn();

	int GetNumFactions() const;
	Faction& GetFaction( int iIndex );

	void Start();
	void End();

	World& GetWorld();

protected:
	virtual void VOnTurnStart( Faction& faction )=0;
	virtual void VOnTurnEnd( Faction& faction )=0;

private:
	GameData m_GameData;

	World* m_pWorld;

	// Factions (Players/AI)
	std::vector< Faction > m_Factions;
	int	m_iCurrentFaction;
	// 
	
	// All cities in game
	std::vector< City* > m_Cities;

	//
	int m_iCurrentPlayer;
	int m_iCurrentDay;
	int m_iCurrentWeek;

	void CreatePlayers( int iNumPlayers );
	void InitPlayer( Faction& pFaction );

	City* CreateCity( const Point& pos, Faction& owner );

	//
	void OnTurnStart( Faction& faction );
	void OnTurnEnd( Faction& faction );
};