#include "pch.h"

#include "XMLParseHelperScope.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"

using namespace MahatmaGameEngine;
using namespace std;

void XMLParseHelperScope::initialize()
{
	mHandledTags.pushBack("Scope");
	mHandledTags.pushBack("World");
	mHandledTags.pushBack("Sector");
	mHandledTags.pushBack("Entity");
	//mHandledTags.pushBack("File");
}

XMLParseHelper* XMLParseHelperScope::clone()
{
	return new XMLParseHelperScope;
}

bool XMLParseHelperScope::startElementHandler(XMLParseMaster::SharedData* sharedData, const std::string& name, HashMap<string, string>& attributesMap)
{
	bool tagFound = false;

	if (sharedData->is(SharedDataTable::typeIdClass()))
	{
		for (uint32_t i = 0; i < mHandledTags.size(); ++i)
		{
			if ((mHandledTags[i] == name))
			{
				tagFound = true;

				// If depth of sharedData is greater than zero, 
				// then append a scope to the sharedData scope and set the scope pointer to the new scope
				// i.e. increase the depth of SharedDataTable.
				if (sharedData->depth() > 0)
				{
					scopeStartHandler(i, *(static_cast<SharedDataTable*>(sharedData)), attributesMap);
					break;
				}
			}
		}
	}

	return tagFound;
}

bool XMLParseHelperScope::endElementHandler(XMLParseMaster::SharedData* sharedData, const string& name)
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
					static_cast<SharedDataTable*>(sharedData)->mCurrentTable = static_cast<SharedDataTable*>(sharedData)->mCurrentTable->getParent();
					break;
				}
			}
		}
	}

	return handled;
}

void XMLParseHelperScope::scopeStartHandler(uint32_t index, SharedDataTable& sharedData, HashMap<string, string>& attributesMap)
{
	switch (index)
	{
	case 0:
	{
		sharedData.mCurrentTable = &(sharedData.mCurrentTable->appendScope(attributesMap["name"]));
		break;
	}
	case 1:
	{
		World* world = new World(attributesMap["name"]);
		sharedData.mCurrentTable->adopt(world, attributesMap["name"]);
		sharedData.mCurrentTable = world;
		break;
	}
	case 2:
	{
		assert(sharedData.mCurrentTable->is(World::typeName()));
		Sector* temp = &(static_cast<World*>(sharedData.mCurrentTable)->createSector(attributesMap["name"]));
		sharedData.mCurrentTable = temp;
		break;
	}
	case 3:
	{
		assert(sharedData.mCurrentTable->is(Sector::typeName()));
		sharedData.mCurrentTable = &(static_cast<Sector*>(sharedData.mCurrentTable)->createEntity(attributesMap["class"], attributesMap["name"]));
		break;
	}
	}
}