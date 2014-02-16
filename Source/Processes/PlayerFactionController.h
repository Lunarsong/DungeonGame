#pragma once
#include "factioncontroller.h"
#include <UI/UserInterface.h>
#include <Core/Input/InputHandlers.h>
#include "../Menus/CityMenu.h"

class PlayerFactionController :
	public FactionController, public IMouseHandler
{
public:
	PlayerFactionController( Game* pGame );
	virtual ~PlayerFactionController(void);

	virtual void VOnInit(void);
	virtual void VOnUpdate( const float fDeltaSeconds );
	virtual void VOnSuccess(void);
	virtual void VOnAbort(void);

	Point MouseToTilePos( const Vector3& vPosition );

	// Mouse handling
	virtual bool VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition );
	virtual bool VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition );
	virtual bool VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition );
	virtual bool VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition );
	virtual bool VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta );

private:
	Engine::SmartPtr<Engine::UIElement> m_pHUD;
	Point m_GameMousePos;

	CityMenu m_CityMenu;
};

