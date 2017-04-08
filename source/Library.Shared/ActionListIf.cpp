#include "pch.h"
#include "ActionListIf.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(ActionListIf)

ActionListIf::ActionListIf()
{
	setTheThisAttribute();
	appendExternalAttribute("condition", &mCondition);
	addToPrescribed("condition");
	adopt(new ActionList, "then");
	addToPrescribed("then");
	adopt(new ActionList, "else");
	addToPrescribed("else");
}

void ActionListIf::setCondition(const std::string& condition)
{
	mCondition = condition;
}

Action& ActionListIf::createAction(const string& className, const string& instanceName, bool isThenAction)
{
	string actionContainer;
	uint32_t index;
	if (isThenAction)
	{
		index = 0;
		actionContainer = "then";
	}
	else
	{
		index = 1;
		actionContainer = "else";
	}

	Action* temp = Factory<Action>::create(className);
	assert(temp != nullptr);
	temp->setName(instanceName);

	adopt(temp, actionContainer);

	return *temp;
}

void ActionListIf::update(WorldState& worldState)
{
	worldState.mCurrentAction = this;

	Scope* temp;
	Datum* condition = search(mCondition, &temp);

	Datum thenActions;
	if ((condition->get<int32_t>()) > 0)
	{
		thenActions = (*this)["then"];

	}
	else
	{
		thenActions = (*this)["else"];
	}

	uint32_t size = thenActions.size();
	for (uint32_t i = 0; i < size; ++i)
	{
		if (thenActions[i].is(Action::typeName()))
		{
			static_cast<Action&>(thenActions[i]).update(worldState);
		}
	}
}

