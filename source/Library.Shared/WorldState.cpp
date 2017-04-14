#include "pch.h"

#include "WorldState.h"

namespace MahatmaGameEngine
{
	WorldState::WorldState() :
		mCurrentWorld(nullptr), mCurrentSector(nullptr), mCurrentEntity(nullptr), mCurrentAction(nullptr), mGameTime(nullptr), mEventQueue(nullptr)
	{
	}
}