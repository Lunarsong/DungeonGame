#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

const Resource& Player::GetResource( Resource::Resources eType ) const
{
	return m_Resources[ eType ];
}
