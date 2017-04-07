#include "pch.h"

#include "ActionList.h"
#include "Attributed.h"
#include "WorldState.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(ActionList)

ActionList::ActionList()
{
	setTheThisAttribute();
	appendExternalAttribute("name", &mName);
	addToPrescribed("name");
	(*this)["actions"].setType(DatumType::TABLE);
	addToPrescribed("actions");
}

Action& ActionList::createAction(const std::string& className, const std::string& instanceName)
{
	Action* temp = Factory<Action>::create(className);
	assert(temp != nullptr);
	temp->setName(instanceName);

	adopt(temp, "actions");

	return *temp;
}

void ActionList::update(WorldState& worldState)
{
	worldState.mCurrentAction = this;

	Datum& actions = (*this)["actions"];
	assert(actions.type() == DatumType::TABLE);
	uint32_t actionsSize = actions.size();

	for (uint32_t i = 0; i < actionsSize; ++i)
	{
		assert(actions[i].is(Action::typeName()));
		static_cast<Action&>(actions[i]).update(worldState);
	}
}