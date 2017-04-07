#include "pch.h"

#include "XMLParseHelperAction.h"
#include "World.h"
#include "Action.h"
#include "Entity.h"
#include "Sector.h"
#include "ActionList.h"

using namespace MahatmaGameEngine;
using namespace std;

XMLParseHelperAction::XMLParseHelperAction()
{
	mHandledTags.pushBack("Action");
	mHandledTags.pushBack("condition");
	mHandledTags.pushBack("then");
	mHandledTags.pushBack("else");
	mHandledTags.pushBack("ActionCreateAction");
	mHandledTags.pushBack("ActionDestroyAction");
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
					//endElementHandler();
					static_cast<SharedDataTable*>(sharedData)->mCurrentTable = static_cast<SharedDataTable*>(sharedData)->mCurrentTable->getParent();
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
		assert(sharedData.mCurrentTable->is(Entity::typeName()) || sharedData.mCurrentTable->is(ActionList::typeName()));
		Action* temp = &(static_cast<Entity*>(sharedData.mCurrentTable)->createAction(attributesMap["class"], attributesMap["name"]));
		sharedData.mCurrentTable = temp;
		break;
	}
	}
}