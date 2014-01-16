#pragma once

#include <UI/UserInterface.h>

class GameMenu
{
public:
	GameMenu(void);
	~GameMenu(void);

	void Show();
	void Hide();

private:
	Engine::UIElement* m_pMenu;
};

