#include "pch.h"
#include "Entity.h"
#include "WorldState.h"
#include "Sector.h"
#include "Scope.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(Entity)

Entity::Entity()
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
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

void Entity::update(WorldState& worldState)
{
	worldState.mCurrentEntity = this;
}