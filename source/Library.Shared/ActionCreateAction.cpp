#include "pch.h"
#include "ActionCreateAction.h"
#include "Factory.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(ActionCreateAction)

ActionCreateAction::ActionCreateAction()
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
	appendExternalAttribute("prototype", &mPrototype);
	addToPrescribed("prototype");
}

ActionCreateAction::ActionCreateAction(const string& name, const string& prototype) :
	mName(name), mPrototype(prototype)
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
	appendExternalAttribute("prototype", &mPrototype);
	addToPrescribed("prototype");
}

void ActionCreateAction::setPropertiesForAction(const string& name, const string& prototype)
{
	mName = name;
	mPrototype = prototype;
}

void ActionCreateAction::update(WorldState & worldState)
{
	worldState.mCurrentAction = this;

	Action* temp = Factory<Action>::create(mPrototype);
	assert(temp != nullptr);
	temp->setName(mName);

	assert(temp->is(Action::typeName()) || temp->is(Entity::typeName()) || temp->is(Sector::typeName()) || temp->is(World::typeName()));
	getParent()->adopt(temp, "actions");
}