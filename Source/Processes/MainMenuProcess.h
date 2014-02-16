#pragma once

#include <Core/Process/Process.h>
#include <Core/Input/InputHandlers.h>
#include <Core/EventManager/IEventManager.h>
#include <UI/UserInterface.h>

using namespace Engine;

class MainMenuProcess : public Engine::Process
{
public:
	MainMenuProcess(void);
	~MainMenuProcess(void);

	virtual void VOnInit(void);
	virtual void VOnUpdate( const float fDeltaSeconds );
	virtual void VOnSuccess(void);
	virtual void VOnFail(void);
	virtual void VOnAbort(void);

private:

};

