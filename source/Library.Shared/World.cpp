#include "pch.h"
#include "World.h"
#include "WorldState.h"
#include "Sector.h"
#include "Action.h"
#include "Datum.h"
#include "Factory.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(World)

World::World()
{
	populateAttributed();
}

World::World(const string& name) :
	mName(name)
{
	populateAttributed();
}

World::World(World&& obj) :
	mName(obj.mName), Attributed(move(obj))
{
}

World& World::operator=(World&& obj)
{
	if (this != &obj)
	{
		mName = obj.mName;
		Attributed::operator=(move(obj));
	}
	return *this;
}

std::string& World::name()
{
	return mName;
}

void World::setName(const std::string& name)
{
	mName = name;
}

Sector& World::createSector()
{
	Sector& temp = *(new Sector);
	addNestedScope("sectors", temp);
	return temp;
}

Sector& World::createSector(const string& sectorName)
{
	Sector& temp = *(new Sector(sectorName));
	addNestedScope("sectors", temp);
	return temp;
}

Action& World::createAction(const string& actionName, const string& instanceName)
{
	Action* temp = Factory<Action>::create(actionName);
	assert(temp != nullptr);
	temp->setName(instanceName);

	adopt(temp, "actions");

	return *temp;
}

Datum& World::sectors()
{
	return append("sectors");
}

void World::update(WorldState& worldState)
{
	worldState.mCurrentWorld = this;

	Datum& sectors = (*this)["sectors"];
	uint32_t sectorsSize = sectors.size();

	for (uint32_t i = 0; i < sectorsSize; ++i)
	{
		assert(sectors[i].is(Sector::typeName()));
		static_cast<Sector&>(sectors[i]).update(worldState);
	}

	Datum& actions = (*this)["actions"];
	uint32_t actionSize = actions.size();

	for (uint32_t i = 0; i < actionSize; ++i)
	{
		assert(actions[i].is(Action::typeName()));
		static_cast<Action&>(actions[i]).update(worldState);
	}
}

void World::populateAttributed()
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
	addToPrescribed("sectors");
}