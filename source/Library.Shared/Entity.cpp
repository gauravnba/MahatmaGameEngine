#include "pch.h"
#include "Entity.h"
#include "WorldState.h"
#include "Sector.h"
#include "Scope.h"
#include "Action.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(Entity)

Entity::Entity()
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
	addToPrescribed("actions");
}

Entity::Entity(Entity&& obj) :
	mName(obj.mName), Attributed(move(obj))
{
}

Entity& Entity::operator=(Entity&& obj)
{
	if (this != &obj)
	{
		mName = obj.mName;
		Attributed::operator=(move(obj));
	}

	return *this;
}

void Entity::setName(const std::string& name)
{
	mName = name;
}

string& Entity::name()
{
	return mName;
}

Sector* Entity::getSector()
{
	assert(getParent()->is(Sector::typeName()));
	return static_cast<Sector*>(getParent());
}

Action& Entity::createAction(const string& className, const string& instanceName)
{
	Action* temp = Factory<Action>::create(className);
	assert(temp != nullptr);
	temp->setName(instanceName);

	adopt(temp, "actions");

	return *temp;
}

void Entity::update(WorldState& worldState)
{
	worldState.mCurrentEntity = this;
	Datum& actions = (*this)["actions"];
	uint32_t size = actions.size();
	for (uint32_t i = 0; i < size; ++i)
	{
		assert(actions[i].is(Action::typeName()));
		static_cast<Action&>(actions[i]).update(worldState);
	}
}