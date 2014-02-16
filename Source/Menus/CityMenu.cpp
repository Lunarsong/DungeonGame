#include "CityMenu.h"


CityMenu::CityMenu(void)
{
	m_pMenu = Engine::UserInterface::AddScreenFromFile( "City", "Screens/CityMenu.xml" );
	auto pLoader = new Engine::UIListLoaderText();
	m_pMenu->GetElement<Engine::UIList>( "build_list_structures" )->SetListLoader( pLoader );
	pLoader->Release();
}


CityMenu::~CityMenu(void)
{

}

void CityMenu::SetCity( City* pCity )
{
	m_pMenu->GetElement<Engine::UIList>( "build_list_structures" )->ClearElements();
	m_pCity = pCity;

	const auto& producibles = pCity->GetProducibles();

	for ( auto it : producibles )
	{
		m_pMenu->GetElement<Engine::UIList>( "build_list_structures" )->AddElement( it->GetName().getStr() );
	}
}

City* CityMenu::GetCity()
{
	return m_pCity;
}
