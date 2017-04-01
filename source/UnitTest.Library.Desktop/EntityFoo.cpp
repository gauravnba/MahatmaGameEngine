#include "pch.h"
#include "Entity.h"
#include "WorldState.h"
#include "EntityFoo.h"

using namespace UnitTestLibraryDesktop;
using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(EntityFoo)

EntityFoo::EntityFoo() :
	mCounter(0)
{
}

std::uint32_t EntityFoo::getCounterValue()
{
	return mCounter;
}

void EntityFoo::update(MahatmaGameEngine::WorldState& worldState)
{
	worldState.mCurrentEntity = this;
	++mCounter;
}