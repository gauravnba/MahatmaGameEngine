#include "pch.h"

#include "XMLParseHelperInteger.h"
#include "SharedDataTable.h"

using namespace MahatmaGameEngine;
using namespace std;

void XMLParseHelperInteger::initialize()
{
}

XMLParseHelper* XMLParseHelperInteger::clone()
{
	return new XMLParseHelperInteger;
}

bool XMLParseHelperInteger::startElementHandler(XMLParseMaster::SharedData* sharedData, const std::string& name, HashMap<std::string, std::string>& attributesMap)
{
	bool tagFound = false;

	if ((mHandledTag == name) && sharedData->is(SharedDataTable::typeIdClass()))
	{
		tagFound = true;
		Scope& tempScope = *(sharedData->as<SharedDataTable>()->mCurrentTable); 
		tempScope[attributesMap["name"]].setType(DatumType::INTEGER);
		tempScope[attributesMap["name"]].setFromString(attributesMap["value"]);
	}

	return tagFound;
}

void XMLParseHelperInteger::charDataHandler(XMLParseMaster::SharedData* sharedData, const char* buffer, std::uint32_t length)
{
	UNREFERENCED_PARAMETER(sharedData);
	UNREFERENCED_PARAMETER(buffer);
	UNREFERENCED_PARAMETER(length);
}

bool XMLParseHelperInteger::endElementHandler(XMLParseMaster::SharedData* sharedData, const string& name)
{
	bool handled = false;
	if ((mHandledTag == name) && sharedData->is(SharedDataTable::typeIdClass()))
	{
		handled = true;
	}

	return handled;
}