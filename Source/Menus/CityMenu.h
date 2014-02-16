#pragma once


#include "../Game/Faction/City.h"
#include <UI/UserInterface.h>


class CityMenu
{
public:
	CityMenu(void);
	~CityMenu(void);

	void SetCity( City* pCity );
	City* GetCity();

private:
	City* m_pCity;
	Engine::UIElement* m_pMenu;
};

