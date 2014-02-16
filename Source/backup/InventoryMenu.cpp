#include "InventoryMenu.h"
#include <Engine.h>
#include "Item.h"
#include "Consumable.h"

using namespace Engine;

InventoryMenu::InventoryMenu(void)
{
	m_pMenu		= Engine::UserInterface::AddScreenFromFile( "GameInventory", "Inventory.xml" );
	m_pMenu->SetVisible( false, true );

	/*((Engine::UIButton*)m_pMenu->GetElement( "btn_resume" ))->SetCallbackFunction( [ this ] ( Engine::UIElement* pElement, void* pData )
	{
		Hide();
	}
	);


	((Engine::UIButton*)m_pMenu->GetElement( "btn_options" ))->SetCallbackFunction( [ this ] ( Engine::UIElement* pElement, void* pData )
	{
		Hide();
	}
	);


	((Engine::UIButton*)m_pMenu->GetElement( "btn_exit" ))->SetCallbackFunction( [ this ] ( Engine::UIElement* pElement, void* pData )
	{
		Engine::BaseApplication::Get()->VQuit();
	}
	);*/

	for ( int i = 0; i < 25; ++i )
	{
		UIButton* pButton = (UIButton*)m_pMenu->GetElement( "btn_" + ToString( i ) );
		if ( !pButton )
		{
			continue;			
		}

		pButton->SetCallbackArgs( (void*)i );
		pButton->SetCallbackFunction( [=] ( UIElement* pElement, void* pArgs ) 
		{
			if ( m_pCharacter )
			{
				Item* pItem = m_pCharacter->GetEquipment().GetInventory().GetItems()[ (int)i ];

				if ( pItem )
				{
					if ( pItem->Type == Item::Usable )
					{
						((Consumable*)pItem)->VOnUse( m_pCharacter );
					}

					else
					{
						m_pCharacter->GetEquipment().Equip( pItem );
					}
				}				
				
			}
		}
		);
	}
	
	
}


InventoryMenu::~InventoryMenu(void)
{
	Engine::UserInterface::RemoveScreen( m_pMenu );
}

void InventoryMenu::Show()
{
	m_pMenu->SetVisible( true, true );
}

void InventoryMenu::Hide()
{
	m_pMenu->SetVisible( false, true );
}

void InventoryMenu::UpdateContents( Inventory& inventory )
{
	const auto& items = inventory.GetItems();

	for ( int i = 0; i < 25; ++i )
	{
		UIImage* pImage = (UIImage*)m_pMenu->GetElement( "img_" + ToString( i ) );
		if ( pImage )
		{
			Item* pItem = items[ i ];
			if ( pItem )
			{
				pImage->SetTexture( pItem->Icon );
			}

			else
			{
				pImage->SetTexture( "" );
			}
			
		}
	}
}

void InventoryMenu::ToggleVisibility()
{
	m_pMenu->SetVisible( !m_pMenu->IsVisible(), true );
}

void InventoryMenu::SetCharacter( Character* pCharacter )
{
	m_pCharacter = pCharacter;
}
