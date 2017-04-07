#include "pch.h"
#include "ActionDestroyAction.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(ActionDestroyAction)

ActionDestroyAction::ActionDestroyAction()
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
}

ActionDestroyAction::ActionDestroyAction(const string& name) :
	mAction(name)
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
}

void ActionDestroyAction::setAction(const string& actionName)
{
	mAction = actionName;
}

void ActionDestroyAction::update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	bool found = false;

	Scope* parent = getParent();

	while (!found && parent != nullptr)
	{
		Datum& tempDatum = parent->append("actions");
		uint32_t size = tempDatum.size();
		for (uint32_t i = 0; i < size; ++i)
		{
			assert(tempDatum[i].is(Action::typeName()));
			if (static_cast<Action&>(tempDatum[i]).name() == mAction)
			{
				delete &(tempDatum[i]);
				found = true;
				break;
			}
		}
		parent = getParent();
	}
}
