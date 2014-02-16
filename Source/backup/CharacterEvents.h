#include <Core/EventManager/Events.h>
#include "Character.h"

class EventCharacterDied : public Engine::BaseEventData
{
public:
	EventCharacterDied( Character* pCharacter )
	{
		m_pCharacter = pCharacter;
	}

	~EventCharacterDied()
	{

	}

	Character* GetCharacter() { return m_pCharacter; }

	virtual const Engine::EventType & VGetEventType() const 
	{ 
		static const Engine::EventType hEventType( "EventCharacterDied" );
		return hEventType;
	}

	virtual Engine::Event VCopy() const 
	{
		return Engine::Event( new EventCharacterDied( m_pCharacter ) );
	}
private:
	Character* m_pCharacter;
};