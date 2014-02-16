#pragma once

#include <Core/Process/Process.h>
#include <Core/EventManager/IEventManager.h>
#include <UI/UserInterface.h>
#include "../Game/Game.h"
#include <Game/Game.h>
#include <Game/Entities/Components/Rendering/CameraComponent.h>
#include "PlayerFactionController.h"
#include "AIFactionController.h"

class GameProcess : public Engine::Process, public Game
{
public:
	GameProcess(void);
	GameProcess( unsigned long ulSeed );
	~GameProcess(void);

	virtual void VOnInit(void);
	virtual void VOnUpdate( const float fDeltaSeconds );
	virtual void VOnSuccess(void);
	virtual void VOnFail(void);
	virtual void VOnAbort(void);

protected:
	virtual void VOnTurnStart( Faction& faction );
	virtual void VOnTurnEnd( Faction& faction );

private:
	Engine::SmartPtr<Engine::Entity> m_pCameraEntity;
	Engine::SmartPtr<Engine::CameraComponent> m_pCamera;  

	int m_iPlayerIndex;
	SmartPtr<PlayerFactionController>	m_pPlayerController;
	SmartPtr<AIFactionController>		m_pAIController;

	void CreateControllers();
};

