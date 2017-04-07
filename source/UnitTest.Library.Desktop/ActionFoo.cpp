#include "pch.h"
#include "ActionFoo.h"
#include "WorldState.h"

using namespace UnitTestLibraryDesktop;
using namespace MahatmaGameEngine;

RTTI_DEFINITIONS(ActionFoo)

ActionFoo::ActionFoo() :
	mUpdateCounter(0)
{
}

std::uint32_t ActionFoo::getCounterValue()
{
	return mUpdateCounter;
}

void ActionFoo::update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	++mUpdateCounter;
}