#include "GameHUDProcess.h"


GameHUDProcess::GameHUDProcess(void)
{
	m_pPlayer			= NULL;

	m_pHud				= NULL;

	m_pGoldLabel		= NULL;
	m_pWoodLabel		= NULL;
	m_pStoneLabel		= NULL;
	m_pCrystalsLabel	= NULL;

	m_pPlayer = new Player();
}


GameHUDProcess::~GameHUDProcess(void)
{
	if ( m_pHud )
	{
		UserInterface::RemoveScreen( m_pHud );
	}
}

void GameHUDProcess::VOnInit( void )
{
	m_pHud = UserInterface::AddScreenFromFile( "Interface", "Screens/GameHUD.xml" );
	m_pGoldLabel		= (UILabel*)m_pHud->GetElement( "lbl_gold" );
	m_pWoodLabel		= (UILabel*)m_pHud->GetElement( "lbl_wood" );
	m_pStoneLabel		= (UILabel*)m_pHud->GetElement( "lbl_stone" );
	m_pCrystalsLabel	= (UILabel*)m_pHud->GetElement( "lbl_crystal" );
}

void GameHUDProcess::VOnUpdate( const float fDeltaSeconds )
{
	if ( m_pPlayer == NULL )
	{
		if ( m_pHud->IsVisible() )
		{
			m_pHud->SetVisible( false, true );
		}		

		return;
	}

	if ( !m_pHud->IsVisible() )
	{
		m_pHud->SetVisible( true, true );
	}

	m_pGoldLabel->SetString( ToString( m_pPlayer->GetResource( Resource::Gold ).GetAmount() ) );
	m_pWoodLabel->SetString( ToString( m_pPlayer->GetResource( Resource::Wood ).GetAmount() ) );
	m_pStoneLabel->SetString( ToString( m_pPlayer->GetResource( Resource::Stone ).GetAmount() ) );
	m_pCrystalsLabel->SetString( ToString( m_pPlayer->GetResource( Resource::Crystals ).GetAmount() ) );
}
