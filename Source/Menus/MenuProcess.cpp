#include "MenuProcess.h"


MenuProcess::MenuProcess(void)
{
	m_pMenu = NULL;
}


MenuProcess::~MenuProcess(void)
{
	if ( m_pMenu )
	{
		m_pMenu->Release();
		m_pMenu = NULL;
	}
}

void MenuProcess::VOnInit( void )
{
	m_pMenu = Engine::UserInterface::AddScreenFromFile( VGetMenuFile(), VGetMenuFile() );
	if ( m_pMenu )
	{
		m_pMenu->AddRef();
	}	
}

void MenuProcess::VOnSuccess( void )
{
	Engine::UserInterface::RemoveScreen( m_pMenu );
}
