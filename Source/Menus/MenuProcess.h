#pragma once

#include <Core/Process/Process.h>
#include <UI/UserInterface.h>

class MenuProcess : public Engine::Process
{
public:
	MenuProcess(void);
	virtual ~MenuProcess(void);

	virtual const char* VGetMenuFile() const=0;

	virtual void VOnInit(void);
	virtual void VOnUpdate( const float fDeltaSeconds ) { }
	virtual void VOnSuccess(void);

protected:
	Engine::UIElement* m_pMenu;
};

