#include "TileActionMenu.h"


TileActionMenu::TileActionMenu(void)
{

}


TileActionMenu::~TileActionMenu(void)
{
}

void TileActionMenu::SetCharacter( Character* pCharacter )
{
	m_pCharacter = pCharacter;
}

void TileActionMenu::Hide()
{
	if ( m_pElement )
	{
		m_pElement->SetVisible( false, true );
	}
}

void TileActionMenu::Show()
{
	if ( m_pElement )
	{
		m_pElement->SetVisible( true, true );
	}
}

void TileActionMenu::Update( float fDeltaSeconds )
{
	if ( m_pCharacter )
	{

	}
}
