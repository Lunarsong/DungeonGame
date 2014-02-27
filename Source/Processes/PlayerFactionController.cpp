#include "PlayerFactionController.h"
#include <Rendering/Scene/SceneManager.h>
#include <Rendering/Utils/RenderUtils.h>
#include <Rendering/Utils/DebugRenderer.h>
#include <Core/Logging/Log.h>


PlayerFactionController::PlayerFactionController( Game* pGame ) : FactionController( pGame )
{
	m_pHUD = Engine::UserInterface::AddScreenFromFile( "Screens/GameHUD.xml", "Screens/GameHUD.xml" );
	m_pHUD->SetVisible( false );

	m_pHUD->GetElement<UIButton>( "btn_end_turn" )->SetCallbackFunction( [=] (Engine::UIElement* pElement, void* pArgs )
		{
			EndTurn();
		});
}

PlayerFactionController::~PlayerFactionController(void)
{
}

void PlayerFactionController::VOnInit( void )
{
	FactionController::VOnInit();
	m_pHUD->SetVisible( true );

	InputManager::Get()->AddMouseHandler( this );
}

void PlayerFactionController::VOnUpdate( const float fDeltaSeconds )
{
	FactionController::VOnUpdate( fDeltaSeconds );

	Vector3 vCenter = GetGame()->GetWorld().GetPositionForTile( m_GameMousePos.x, m_GameMousePos.y );

	DebugRenderer::AddAABB( vCenter - Vector3::ONE * 0.5f, vCenter + Vector3::ONE * 0.5f, ColorF::GREEN );
}

void PlayerFactionController::VOnSuccess( void )
{
	FactionController::VOnSuccess();
	m_pHUD->SetVisible( false );
	InputManager::Get()->RemoveMouseHandler( this );
}

void PlayerFactionController::VOnAbort( void )
{
	FactionController::VOnAbort();
	m_pHUD->SetVisible( false );
	InputManager::Get()->RemoveMouseHandler( this );
}

Point PlayerFactionController::MouseToTilePos( const Vector3& vPosition )
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

	return GetGame()->GetWorld().GetTilePosition( vGroundPosition );
}

bool PlayerFactionController::VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition )
{
	m_GameMousePos = MouseToTilePos( vPosition );

	return false;
}

bool PlayerFactionController::VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition )
{
	return false;
}

bool PlayerFactionController::VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition )
{
	Point pos = MouseToTilePos( vPosition );
	if ( pos.x > 0 && pos.y > 0 && pos.x < GetGame()->GetWorld().GetTileMap().SizeX() && pos.y < GetGame()->GetWorld().GetTileMap().SizeY() )
	{
		auto& entities = GetGame()->GetWorld().GetTileMap()( pos.x, pos.y ).mEntities;
		for ( auto it : entities )
		{
			if ( it->GetComponent<City>() )
			{
				Engine::Log << "Whee";
				City* pCity = it->GetComponent<City>();
				const std::vector< const Engine::Entity* >& prods = pCity->GetProducibles();

				if ( prods.size() )
				{
					m_CityMenu.SetCity( pCity );
				}
			

			}
		}
	}

	return false;
}

bool PlayerFactionController::VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition )
{
	return false;
}

bool PlayerFactionController::VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta )
{
	return false;
}
