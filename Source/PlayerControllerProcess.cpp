//
//  PlayerControllerProcess.cpp
//  DungeonGame
//
//  Created by Shanee on 1/7/14.
//
//

#include "PlayerControllerProcess.h"
#include <Rendering/Utils/RenderUtils.h>
#include <Rendering/Scene/SceneManager.h>
#include <Game/Entities/Components/Rendering/RenderComponent.h>
#include <Game/Entities/Entity.h>
#include <Engine.h>
#include <Rendering/Scene/SceneManager.h>
#include <Game/Entities/Components/Rendering/CameraComponent.h>
#include <Engine.h>
#include "DungeonGame.h"
#include <Rendering/Utils/DebugRenderer.h>

PlayerControllerProcess::PlayerControllerProcess()
{
	m_pTargetNode = NULL;
	m_eInputState = NoInput;

	m_pHUD		= UserInterface::AddScreenFromFile( "GameHUD", "GameHUD.xml" );
	m_pExperienceProgress = (UIProgressBar*)m_pHUD->GetElement( "progress_xp" );
	m_pActionsHUD = m_pHUD->GetElement( "anchor_action" );
	m_pActionsHUD->SetVisible( false, true );

	((UIButton*)m_pHUD->GetElement( "btn_menu" ))->SetCallbackFunction( [ this ] ( UIElement* pElement, void* pData )
	{
		m_GameMenu.Show();
	}
	);

	((UIButton*)m_pHUD->GetElement( "btn_character" ))->SetCallbackFunction( [ this ] ( UIElement* pElement, void* pData )
	{
		m_InventoryMenu.UpdateContents( m_pCharacter->GetEquipment().GetInventory() );
		m_InventoryMenu.ToggleVisibility();
		m_CharacterMenu.ToggleVisibility();
	}
	);
}

PlayerControllerProcess::~PlayerControllerProcess()
{
    
}

void PlayerControllerProcess::VOnInit()
{
	CharacterControllerProcess::VOnInit();

    m_ePlayerState = AwaitingInput;
	m_eInputState = NoInput;
    
    InputManager::Get()->AddMouseHandler( this );
}

void PlayerControllerProcess::VOnSuccess()
{
    InputManager::Get()->RemoveMouseHandler( this );

	CharacterControllerProcess::VOnSuccess();
}

void PlayerControllerProcess::VOnFail()
{
    InputManager::Get()->RemoveMouseHandler( this );

	CharacterControllerProcess::VOnFail();
}

void PlayerControllerProcess::VOnAbort()
{
    InputManager::Get()->RemoveMouseHandler( this );

	CharacterControllerProcess::VOnAbort();
}

void PlayerControllerProcess::VOnUpdate( const float fDeltaSeconds )
{
	CharacterControllerProcess::VOnUpdate( fDeltaSeconds );
	m_InventoryMenu.UpdateContents( m_pCharacter->GetEquipment().GetInventory() );
	m_InventoryMenu.SetCharacter( m_pCharacter );
	m_CharacterMenu.Update( m_pCharacter );

	UpdateHealthAndMana();
	DrawGrid();

	if ( m_eInputState == NoInput )
	{
		
	}

	else if ( m_eInputState == Pressed )
	{
		m_fInputTimer += fDeltaSeconds;

		static const float k_fPressToMenuTime = 0.8f;
		if ( m_fInputTimer >= k_fPressToMenuTime )
		{
			m_pActionsHUD->SetRelativePosition( Vector3::ZERO );
			m_pActionsHUD->SetPosition( m_vInitialPressLoc );
			m_pActionsHUD->SetVisible( true, true );

			m_eInputState = Menu;
		}
	}

	else if ( m_eInputState == Scroll )
	{
		CameraComponent* pCamera = (CameraComponent*)SceneManager::Get()->GetActiveCamera();
		if ( pCamera )
		{
			Vector4 vCameraPosition = pCamera->GetTransform().GetPosition();

			static const float k_fScrollSpeed = 0.005f;
			vCameraPosition.x -= m_vInputDeltaPosition.x * k_fScrollSpeed;// * fDeltaSeconds;
			vCameraPosition.z += m_vInputDeltaPosition.y * k_fScrollSpeed;// * fDeltaSeconds;

			m_vInputDeltaPosition = Vector3::ZERO;

			pCamera->GetTransform().SetPosition( vCameraPosition );
		}
	}
}

bool PlayerControllerProcess::VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition )
{
	const Camera* pCamera = SceneManager::Get()->GetActiveCamera();
	Vector3 vScreenPos = vPosition;
	Vector3 vRayPos, vRayDir;
	RenderUtils::Unproject( vScreenPos, pCamera->GetProjection(), pCamera->GetView(), vRayPos, vRayDir );
	vRayDir.Normalize();
	Plane groundPlane;
	groundPlane.InitFromPointNormal( Vector3::ZERO, Vector3::UP );

	Vector3 vGroundPosition;
	IntersectionUtils::RayPlaneIntersect( vRayPos, vRayPos + vRayDir * 1000.0f, groundPlane, vGroundPosition );
	m_pTargetNode = m_pPathGraph->VFindClosestNode( vGroundPosition );

	if ( m_eInputState == Pressed )
	{
		static const float k_fScrollThresholdDistanceSQ = 50.0f * 50.0f;
		if ( vPosition.DistanceSQ( m_vInitialPressLoc ) >= k_fScrollThresholdDistanceSQ )
		{
			m_eInputState = Scroll;
		}
	}

	else if ( m_eInputState == Scroll )
	{
		m_vInputDeltaPosition += vDeltaPosition;
	}

    return false;
}

bool PlayerControllerProcess::VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition )
{
	m_eInputState = Pressed;
	m_fInputTimer = 0.0f;
	m_vInitialPressLoc = vPosition;

    return false;
}

bool PlayerControllerProcess::VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition )
{	
	m_pActionsHUD->SetVisible( false, true );

    if ( m_ePlayerState != AwaitingInput )
	{
		m_eInputState = NoInput;
        return false;
	}
	
    
    const Camera* pCamera = SceneManager::Get()->GetActiveCamera();
    
    Vector3 vScreenPos = vPosition;
    Vector3 vRayPos, vRayDir;
    RenderUtils::Unproject( vScreenPos, pCamera->GetProjection(), pCamera->GetView(), vRayPos, vRayDir );
    vRayDir.Normalize();
    Plane groundPlane;
    groundPlane.InitFromPointNormal( Vector3::ZERO, Vector3::UP );
    
    Vector3 vGroundPosition;
    IntersectionUtils::RayPlaneIntersect( vRayPos, vRayPos + vRayDir * 1000.0f, groundPlane, vGroundPosition );


	if ( m_eInputState == Pressed )
	{
		PathfindingNode* pNode = m_pPathGraph->VFindClosestNode( vGroundPosition );
		if ( SelectNode( pNode ) )
		{
			//m_ePlayerState = Processing;
		}

	}
	 
	
    
    
	m_eInputState = NoInput;

    return true;
}

bool PlayerControllerProcess::VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition )
{
    return false;
}

bool PlayerControllerProcess::VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta )
{
    return false;
}

void PlayerControllerProcess::UpdateHealthAndMana()
{
	// Set the health bar
	UIImage* pImage = (UIImage*)m_pHUD->GetElement( "img_health" );
	if ( pImage )
	{
		//int iTextureWidth = pImage->GetSprite().GetTexture()->VGetWidth();
		int iTextureHeight = pImage->GetSprite().GetTexture()->VGetHeight();

		double dHealthPercent = m_pCharacter->GetAttribute( Attributes::Health ).GetPercent();
		RectF uv = pImage->GetSprite().GetUV();
		uv.y = 1.0f - (float)dHealthPercent;
		pImage->GetSprite().SetUV( uv );

		Vector3 vSize = pImage->GetSize().GetCoordinates();
		vSize.y = (float)(iTextureHeight * dHealthPercent);
		pImage->SetSize( vSize );
	}

	// Set the Mana bar
	pImage = (UIImage*)m_pHUD->GetElement( "img_mana" );
	if ( pImage )
	{
		//int iTextureWidth = pImage->GetSprite().GetTexture()->VGetWidth();
		int iTextureHeight = pImage->GetSprite().GetTexture()->VGetHeight();

		double dManaPercent = m_pCharacter->GetAttribute( Attributes::Mana ).GetPercent();
		RectF uv = pImage->GetSprite().GetUV();
		uv.y = 1.0f - (float)dManaPercent;
		pImage->GetSprite().SetUV( uv );

		Vector3 vSize = pImage->GetSize().GetCoordinates();
		vSize.y = (float)(iTextureHeight * dManaPercent);
		pImage->SetSize( vSize );
	}

	int iExperienceForLevel = Character::CalculateExperienceForLevel( m_pCharacter->GetLevel() );
	int iExperienceForNextLevel = Character::CalculateExperienceForLevel( m_pCharacter->GetLevel() + 1 ) - iExperienceForLevel;
	int iExperience = m_pCharacter->GetExperience() - iExperienceForLevel;
	m_pExperienceProgress->SetProgressMax( iExperienceForNextLevel );
	m_pExperienceProgress->SetProgress( iExperience );
}

void PlayerControllerProcess::DrawGrid()
{
	if ( !(m_eInputState == NoInput || m_eInputState == Pressed) || IsProcessing() )
		return;

	static const ColorF k_WalkColor( 0.0f, 0.0f, 1.0f, 0.2f );
	static const ColorF k_LegalColor( 0.0f, 1.0f, 0.0f, 0.2f );
	static const ColorF k_AttackColor( 1.0f, 0.62745098f, 0.0f, 0.6f );
	static const ColorF k_NoneColor( 1.0f, 0.0f, 0.0f, 0.2f );
	
	bool bTargetRendered = false;
	for ( auto it : m_pWalkableNodes )
	{
		Vector3 vPosition = it->GetPosition();
		
		if ( it == m_pTargetNode )
		{
			vPosition.y = 0.5f;
			DebugRenderer::AddAABB( vPosition - Vector3::ONE * 0.5f, vPosition + Vector3::ONE * 0.5f, k_LegalColor, 1.0f, 0.0f );
			bTargetRendered = true;
		}

		else
		{			
			DebugRenderer::AddAABB( vPosition - Vector3::ONE * 0.5f, vPosition + Vector3::ONE * 0.5f, k_WalkColor, 1.0f, 0.0f );
		}
	}

	for ( auto it : m_AttackableCharacters )
	{
		Vector3 vPosition = it->GetTransform().GetPosition();
		DebugRenderer::AddAABB( vPosition - Vector3::ONE * 0.5f, vPosition + Vector3::ONE * 0.5f, k_AttackColor, 1.0f, 0.0f );
	}

	if ( !bTargetRendered && m_pTargetNode )
	{
		Vector3 vPosition = m_pTargetNode->GetPosition();
		vPosition.y = 0.5f;

		
		bool bActionFound = false;
		QueryTileActions( m_pTargetNode, m_ActionsQuery );
		for ( auto it : m_ActionsQuery )
		{
			if ( it == AttackTile )
			{
				DebugRenderer::AddAABB( vPosition - Vector3::ONE * 0.5f, vPosition + Vector3::ONE * 0.5f, k_LegalColor, 1.0f, 0.0f );
				bActionFound = true;
				break;
			}

			else if ( it == WalkTile )
			{
				DebugRenderer::AddAABB( vPosition - Vector3::ONE * 0.5f, vPosition + Vector3::ONE * 0.5f, k_LegalColor, 1.0f, 0.0f );
				bActionFound = true;
				break;
			}
		}

		if ( !bActionFound )
		{
			DebugRenderer::AddAABB( vPosition - Vector3::ONE * 0.5f, vPosition + Vector3::ONE * 0.5f, k_NoneColor, 1.0f, 0.0f );
		}
		
	}
}

void PlayerControllerProcess::SetCharacter( CharacterComponent* pCharacter )
{
	if ( pCharacter && pCharacter != m_pCharacter )
	{
		DungeonGame* pGame = (DungeonGame*)BaseApplication::Get()->GetProcessManager().GetProcessByName( "Game" );
		if ( pGame )
		{
			CameraComponent* pCamera = pGame->GetCamera();
			if ( pCamera )
			{
				Vector4 vCameraPosition = pCamera->GetTransform().GetPosition();
				const Vector3& vCharacterPosition = pCharacter->GetPosition();

				vCameraPosition.x = vCharacterPosition.x;
				vCameraPosition.z = vCharacterPosition.z;

				pCamera->GetTransform().SetPosition( vCameraPosition );
			}
		}
	}	

	CharacterControllerProcess::SetCharacter( pCharacter );
}


