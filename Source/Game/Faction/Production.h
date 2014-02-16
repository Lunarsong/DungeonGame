#pragma once

#include <Externals/HashedString/HashedString.h>
#include <map>

class Production
{
public:
	Production(void);
	~Production(void);

	HashedString	mProduct;
	int				mAmount;

	int				mTurns;
	int				mTurnsLeft;

	std::map< HashedString, int > mResources;
};