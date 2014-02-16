#include "GameProcess.h"

using namespace Engine;

#include <Game/Entities/Components/Rendering/FreeCameraComponent.h>
#include <Core/Application/BaseApplication.h>

GameProcess::GameProcess( void )
{
	m_iPlayerIndex = 0;
}

GameProcess::GameProcess( unsigned long ulSeed )
{

}

GameProcess::~GameProcess( void )
{
}

void GameProcess::VOnInit( void )
{
	m_iPlayerIndex = 0;

	Create( (unsigned int)time(NULL), 64 );

	m_pCameraEntity = GameManager::CreateEntity();
	m_pCamera = new FreeCameraComponent();
	m_pCameraEntity->AddComponent( m_pCamera );
	m_pCameraEntity->GetTransform().SetPosition( Vector3( 0.0f, 5.0f, 0.0f ) );
	m_pCameraEntity->GetTransform().SetDirection( -Vector4::UP );

	m_pCamera->Release();

	CreateControllers();

	Start();
}

void GameProcess::VOnUpdate( const float fDeltaSeconds )
{

}

void GameProcess::VOnSuccess( void )
{

}

void GameProcess::VOnFail( void )
{

}

void GameProcess::VOnAbort( void )
{

}

void GameProcess::VOnTurnStart( Faction& faction )
{
	if ( &faction == &GetFaction( m_iPlayerIndex ) )
	{
		m_pPlayerController->SetFaction( &faction );
		Engine::BaseApplication::Get()->AttachProcess( m_pPlayerController );
	}

	else
	{
		m_pAIController->SetFaction( &faction );
		Engine::BaseApplication::Get()->AttachProcess( m_pAIController );
	}
}

void GameProcess::VOnTurnEnd( Faction& faction )
{
	if ( m_pAIController->IsAlive() )
	{
		m_pAIController->Succeed();
	}

	if ( m_pPlayerController->IsAlive() )
	{
		m_pPlayerController->Succeed();
	}
}

void GameProcess::CreateControllers()
{
	m_pAIController = new AIFactionController( this );
	m_pAIController->Release();

	m_pPlayerController = new PlayerFactionController( this );
	m_pPlayerController->Release();
}
