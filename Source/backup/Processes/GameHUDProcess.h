#pragma once

#include <Core/Process/Process.h>
#include <Core/Input/InputHandlers.h>
#include <UI/UserInterface.h>

#include "../Player.h"

using namespace Engine;
class GameHUDProcess : public Process
{
public:
	GameHUDProcess(void);
	~GameHUDProcess(void);

	virtual void VOnInit(void);
	virtual void VOnUpdate( const float fDeltaSeconds );

private:
	Player*		m_pPlayer;

	UIElement*	m_pHud;

	UILabel* m_pGoldLabel;
	UILabel* m_pWoodLabel;
	UILabel* m_pStoneLabel;
	UILabel* m_pCrystalsLabel;

	void UpdateResources();
};

