#include "pch.h"

#include "XMLParseHelperScope.h"
#include "SharedDataTable.h"

using namespace MahatmaGameEngine;
using namespace std;

void XMLParseHelperScope::initialize()
{
}

XMLParseHelper* XMLParseHelperScope::clone()
{
	return new XMLParseHelperScope;
}

bool XMLParseHelperScope::startElementHandler(XMLParseMaster::SharedData* sharedData, const std::string& name, HashMap<std::string, std::string>& attributesMap)
{
	bool tagFound = false;

	if ((mHandledTag == name) && sharedData->is(SharedDataTable::typeIdClass()))
	{
		tagFound = true;

		// If depth of sharedData is greater than zero, 
		// then append a scope to the sharedData scope and set the scope pointer to the new scope
		// i.e. increase the depth of SharedDataTable.
		if (sharedData->depth() > 0)
		{
			sharedData->as<SharedDataTable>()->mCurrentTable = &((sharedData->as<SharedDataTable>()->mCurrentTable)->appendScope(attributesMap["name"]));
		}
	}

	return tagFound;
}

void XMLParseHelperScope::charDataHandler(XMLParseMaster::SharedData* sharedData, const char* buffer, std::uint32_t length)
{
	UNREFERENCED_PARAMETER(sharedData);
	UNREFERENCED_PARAMETER(buffer);
	UNREFERENCED_PARAMETER(length);
}

bool XMLParseHelperScope::endElementHandler(XMLParseMaster::SharedData* sharedData, const string& name)
{
	bool handled = false;
	if ((mHandledTag == name) && sharedData->is(SharedDataTable::typeIdClass()))
	{
		handled = true;
		if (sharedData->depth() > 0)
		{
			sharedData->as<SharedDataTable>()->mCurrentTable = sharedData->as<SharedDataTable>()->mCurrentTable->getParent();
		}
	}

	return handled;
}