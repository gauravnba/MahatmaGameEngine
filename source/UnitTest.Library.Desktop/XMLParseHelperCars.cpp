#include "pch.h"

#include "XMLParseHelperCars.h"
#include "SharedDataCars.h"

using namespace MahatmaGameEngine;
using namespace UnitTestLibraryDesktop;
using namespace std;

void XMLParseHelperCars::initialize()
{
	mListOfTags.clear();
	mListOfTags.pushBack("Car");
	mListOfTags.pushBack("Land");
}

XMLParseHelperCars* XMLParseHelperCars::clone()
{
	XMLParseHelperCars* temp = new XMLParseHelperCars;
	temp->mListOfTags = mListOfTags;
	return temp;
}

bool XMLParseHelperCars::startElementHandler(XMLParseMaster::SharedData* sharedData, const string& name, HashMap<string, string>& attributesMap)
{
	bool tagFound = false;
	Vector<string>::Iterator helper = mListOfTags.find(name);

	if ((mListOfTags.find(name) != mListOfTags.end()) && sharedData->is(SharedDataCars::typeIdClass()))
	{
		if (name == "Car")
		{
			Scope& tempScope = sharedData->as<SharedDataCars>()->mFoundAttributes.appendScope(name);

			for (pair<string, string> value : attributesMap)
			{
				{
					Datum& tempDatum = tempScope.append(value.first);
					tempDatum.set(value.second, tempDatum.size());
				}
			}
		}
	}

	sharedData->incrementDepth();
	return tagFound;
}

void XMLParseHelperCars::charDataHandler(XMLParseMaster::SharedData* sharedData, const string& buffer)
{
	UNREFERENCED_PARAMETER(sharedData);
	UNREFERENCED_PARAMETER(buffer);
}

bool XMLParseHelperCars::endElementHandler(XMLParseMaster::SharedData* sharedData, const string& name)
{
	bool handled = false;
	if ((mListOfTags.find(name) != mListOfTags.end()) && sharedData->is(SharedDataCars::typeIdClass()))
	{
		handled = true;
	}

	sharedData->decrementDepth();
	return handled;
}