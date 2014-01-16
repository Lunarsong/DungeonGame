//
//  PlayerControllerProcess.h
//  DungeonGame
//
//  Created by Shanee on 1/7/14.
//
//

#pragma once

#include <Core/Process/Process.h>
#include <Core/Input/InputHandlers.h>
#include <Game/Entities/Components/AI/PathFollowerComponent.h>
#include <UI/UserInterface.h>

#include "CharacterComponent.h"
#include "GameMenu.h"
#include "InventoryMenu.h"
#include "CharacterMenu.h"
#include "CharacterControllerProcess.h"

using namespace Engine;

class PlayerControllerProcess : public CharacterControllerProcess, public IMouseHandler
{
public:
    PlayerControllerProcess();
    ~PlayerControllerProcess();
    
    virtual void VOnInit();
    virtual void VOnSuccess();
    virtual void VOnFail();
    virtual void VOnAbort();
    
    virtual void VOnUpdate( const float fDeltaSeconds );
    
    // Mouse handling
    virtual bool VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition );
    virtual bool VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta );
    
private:
	GameMenu		m_GameMenu;
	InventoryMenu	m_InventoryMenu;
	CharacterMenu	m_CharacterMenu;
	
	std::vector< TileAction > m_ActionsQuery;
	
    float m_fTimer;
    
    enum PlayerState
    {
        AwaitingInput,
        Processing,
        Done
    };
    
    PlayerState m_ePlayerState;

	UIElement* m_pHUD;
	UIElement* m_pActionsHUD;

	// Input
	float m_fInputTimer;
	enum InputState
	{
		NoInput,
		Pressed,
		Menu,
		Scroll,

		InputStateCount
	};
	InputState m_eInputState;
	Vector3 m_vInitialPressLoc;
	Vector3 m_vInputDeltaPosition;

	void UpdateHealthAndMana();
	void DrawGrid();
};