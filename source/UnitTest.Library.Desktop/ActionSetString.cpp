#include "pch.h"
#include "ActionSetString.h"
#include "Scope.h"

using namespace MahatmaGameEngine;
using namespace std;

ActionSetString::ActionSetString()
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
	appendExternalAttribute("string", &mString);
	addToPrescribed("string");
	appendExternalAttribute("value", &mStringValue);
	addToPrescribed("value");
}

void ActionSetString::setName(const string& name)
{
	mName = name;
}

void ActionSetString::setStringValues(const string& stringToChange, const string& value)
{
	mString = stringToChange;
	mStringValue = value;
}

void ActionSetString::update(WorldState& worldState)
{
	worldState.mCurrentAction = this;

	Scope** containingScope = nullptr;
	Datum* datumFound = search(mString, containingScope);

	datumFound->set(mStringValue);
}
