#include "pch.h"

#include "XMLParseHelperActionListIf.h"
#include "World.h"
#include "Action.h"
#include "Entity.h"
#include "Sector.h"
#include "ActionList.h"
#include "ActionListIf.h"
#include "ActionSetString.h"

using namespace MahatmaGameEngine;
using namespace std;

XMLParseHelperAction::XMLParseHelperAction() :
	mIsThen(false)
{
	mHandledTags.pushBack("if");
	mHandledTags.pushBack("condition");
	mHandledTags.pushBack("then");
	mHandledTags.pushBack("else");
	mHandledTags.pushBack("Action");
	mHandledTags.pushBack("Reaction");
}

XMLParseHelper* XMLParseHelperAction::clone()
{
	return new XMLParseHelperAction;
}

bool XMLParseHelperAction::startElementHandler(XMLParseMaster::SharedData* sharedData, const string& name, HashMap<string, string>& attributesMap)
{
	bool tagFound = false;

	if (sharedData->is(SharedDataTable::typeIdClass()))
	{
		for (uint32_t i = 0; i < mHandledTags.size(); ++i)
		{
			if (mHandledTags[i] == name)
			{
				tagFound = true;

				// If depth of sharedData is greater than zero, 
				// then append a scope to the sharedData scope and set the scope pointer to the new scope
				// i.e. increase the depth of SharedDataTable.
				if (sharedData->depth() > 0)
				{
					actionStartHandler(*(static_cast<SharedDataTable*>(sharedData)), i, attributesMap);
					break;
				}
			}
		}
	}

	return tagFound;
}

void XMLParseHelperAction::charDataHandler(XMLParseMaster::SharedData* sharedData, const std::string& value)
{
	UNREFERENCED_PARAMETER(sharedData);
	mBuffer.append(value);
}

bool XMLParseHelperAction::endElementHandler(XMLParseMaster::SharedData* sharedData, const std::string& name)
{
	bool handled = false;
	if (sharedData->is(SharedDataTable::typeIdClass()))
	{
		for (uint32_t i = 0; i < mHandledTags.size(); ++i)
		{
			if (mHandledTags[i] == name)
			{
				handled = true;
				if (sharedData->depth() > 0)
				{
					assert(sharedData->is(SharedDataTable::typeName()));
					actionEndHandler(*(static_cast<SharedDataTable*>(sharedData)), i);
					mBuffer.clear();
					break;
				}
			}
		}
	}

	return handled;
}

void XMLParseHelperAction::actionStartHandler(SharedDataTable& sharedData, uint32_t index, HashMap<string, string>& attributesMap)
{
	switch (index)
	{
	case 0:
	{
		assert(sharedData.mCurrentTable->is(World::typeName())
			|| sharedData.mCurrentTable->is(Sector::typeName())
			|| sharedData.mCurrentTable->is(Entity::typeName())
			|| sharedData.mCurrentTable->is(ActionList::typeName()));
		createActionListIf(sharedData, attributesMap["name"]);
		break;
	}
	case 1:
		mBuffer.clear();
		break;
	case 2:
	{
		assert(sharedData.mCurrentTable->is(ActionListIf::typeName()));
		sharedData.mCurrentTable = &((*sharedData.mCurrentTable)["then"][0]);
		mIsThen = true;
		break;
	}
	case 3:
	{
		assert(sharedData.mCurrentTable->is(ActionListIf::typeName()));
		sharedData.mCurrentTable = &((*sharedData.mCurrentTable)["else"][0]);
		mIsThen = false;
		break;
	}
	case 4:
	{
		assert(sharedData.mCurrentTable->is(World::typeName())
			|| sharedData.mCurrentTable->is(Sector::typeName())
			|| sharedData.mCurrentTable->is(Entity::typeName())
			|| sharedData.mCurrentTable->is(ActionList::typeName()));
		createAction(sharedData, attributesMap);
		break;
	}
	case 5:
	{
		assert(sharedData.mCurrentTable->is(World::typeName())
			|| sharedData.mCurrentTable->is(Sector::typeName())
			|| sharedData.mCurrentTable->is(Entity::typeName())
			|| sharedData.mCurrentTable->is(ActionList::typeName()));
		createAction(sharedData, attributesMap);
		break;
	}
	}
}

void XMLParseHelperAction::createActionListIf(SharedDataTable& sharedData, const string& name)
{
	if (sharedData.mCurrentTable->is(World::typeName()))
	{
		Action& temp = static_cast<World*>(sharedData.mCurrentTable)->createAction("ActionListIf", name);
		sharedData.mCurrentTable = &temp;
	}
	else if (sharedData.mCurrentTable->is(Sector::typeName()))
	{
		Action& temp = static_cast<Sector*>(sharedData.mCurrentTable)->createAction("ActionListIf", name);
		sharedData.mCurrentTable = &temp;
	}
	else if (sharedData.mCurrentTable->is(Entity::typeName()))
	{
		Action& temp = static_cast<Entity*>(sharedData.mCurrentTable)->createAction("ActionListIf", name);
		sharedData.mCurrentTable = &temp;
	}
	else if (sharedData.mCurrentTable->is(ActionList::typeName()))
	{
		Action& temp = static_cast<ActionList*>(sharedData.mCurrentTable)->createAction("ActionListIf", name);
		sharedData.mCurrentTable = &temp;
	}
}

void XMLParseHelperAction::actionEndHandler(SharedDataTable& sharedData, uint32_t index)
{
	if(index == 1)
	{
		assert(sharedData.mCurrentTable->is(ActionListIf::typeName()));
		static_cast<ActionListIf*>(sharedData.mCurrentTable)->setCondition(mBuffer);
	}
	else if(index != 5)
	{
		sharedData.mCurrentTable = (sharedData.mCurrentTable->getParent());
	}
}

void XMLParseHelperAction::createAction(SharedDataTable& sharedTable, const HashMap<string, string>& attributes)
{
	Action* temp = nullptr;
	if (sharedTable.mCurrentTable->is(World::typeName()))
	{
		temp = &(static_cast<World*>(sharedTable.mCurrentTable)->createAction(attributes["class"], attributes["name"]));
		sharedTable.mCurrentTable = temp;
	}
	else if (sharedTable.mCurrentTable->is(Sector::typeName()))
	{
		temp = &(static_cast<Sector*>(sharedTable.mCurrentTable)->createAction(attributes["class"], attributes["name"]));
		sharedTable.mCurrentTable = temp;
	}
	else if (sharedTable.mCurrentTable->is(Entity::typeName()))
	{
		temp = &(static_cast<Entity*>(sharedTable.mCurrentTable)->createAction(attributes["class"], attributes["name"]));
		sharedTable.mCurrentTable = temp;
	}
	else if(sharedTable.mCurrentTable->is(ActionList::typeName()))
	{
		temp = &(static_cast<ActionList*>(sharedTable.mCurrentTable)->createAction(attributes["class"], attributes["name"]));
		sharedTable.mCurrentTable = temp;
	}

	assert(temp != nullptr);
	setActionAttributes(*temp, attributes);
}

void XMLParseHelperAction::setActionAttributes(Action& temp, const HashMap<string, string>& attributes)
{
	if (temp.is(ActionSetString::typeName()))
	{
		static_cast<ActionSetString&>(temp).setStringValues(attributes["string"], attributes["value"]);
	}
	else if (temp.is(ActionEvent::typeName()))
	{
		static_cast<ActionEvent&>(temp).setAttributes(attributes["subType"], stoi(attributes["delay"]));
	}
	else if (temp.is(ReactionAttributed::typeName()))
	{
		static_cast<ReactionAttributed&>(temp).setSubType(attributes["subType"]);
	}
}