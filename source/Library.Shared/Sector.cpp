#include "pch.h"
#include "Sector.h"
#include "WorldState.h"
#include "Entity.h"
#include "World.h"
#include "Scope.h"
#include "Action.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(Sector)

Sector::Sector()
{
	populateAttributed();
}

Sector::Sector(const string& name) :
	mName(name)
{
	populateAttributed();
}

Datum& Sector::entities()
{
	return append("entities");
}

void Sector::setName(const std::string& name)
{
	mName = name;
}

string& Sector::name()
{
	return mName;
}

Entity& Sector::createEntity(const string& className, const string& instanceName)
{
	Entity* temp = Factory<Entity>::create(className);
	assert(temp != nullptr);
	temp->setName(instanceName);
	
	adopt(temp, "entities");

	return *temp;
}

Action& Sector::createAction(const std::string & actionName, const std::string & instanceName)
{
	Action* temp = Factory<Action>::create(actionName);
	assert(temp != nullptr);
	temp->setName(instanceName);

	adopt(temp, "actions");

	return *temp;
}

void Sector::adoptEntity(Entity& entity)
{
	adopt(&entity, "entities");
}

World* Sector::getWorld()
{
	assert(getParent()->is(World::typeName()));
	return static_cast<World*>(getParent());
}

void Sector::update(WorldState& worldState)
{
	worldState.mCurrentSector = this;
	
	Datum& entities = (*this)["entities"];
	assert(entities.type() == DatumType::TABLE);
	uint32_t entitiesSize = entities.size();

	for (uint32_t i = 0; i < entitiesSize; ++i)
	{
		assert(entities[i].is(Entity::typeName()));
		static_cast<Entity&>(entities[i]).update(worldState);
	}

	Datum& actions = (*this)["actions"];
	uint32_t actionSize = actions.size();

	for (uint32_t i = 0; i < actionSize; ++i)
	{
		assert(actions[i].is(Action::typeName()));
		static_cast<Action&>(actions[i]).update(worldState);
	}
}

void Sector::populateAttributed()
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
	(*this)["entities"].setType(DatumType::TABLE);
	addToPrescribed("entities");
	(*this)["actions"].setType(DatumType::TABLE);
	addToPrescribed("actions");
	(*this)["reactions"].setType(DatumType::TABLE);
	addToPrescribed("reactions");
}