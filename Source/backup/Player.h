#pragma once

#include "Resources.h"

class Player
{
public:
	Player(void);
	~Player(void);


	const Resource& GetResource( Resource::Resources eType ) const;

private:
	Resource m_Resources[ Resource::ResourcesCount ];
};

