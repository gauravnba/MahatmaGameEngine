#include "pch.h"

#include "XMLParseHelperMotorcycle.h"
#include "SharedDataMotorcycles.h"

using namespace MahatmaGameEngine;
using namespace UnitTestLibraryDesktop;
using namespace std;

void XMLParseHelperMotorcycle::initialize()
{
	mListOfTags.clear();
	mListOfTags.pushBack("Motorcycle");
	mListOfTags.pushBack("Brand");
	mListOfTags.pushBack("Name");
	mListOfTags.pushBack("Category");
}

XMLParseHelperMotorcycle* XMLParseHelperMotorcycle::clone()
{
	XMLParseHelperMotorcycle* temp = new XMLParseHelperMotorcycle;
	temp->mListOfTags = mListOfTags;
	return temp;
}

bool XMLParseHelperMotorcycle::startElementHandler(XMLParseMaster::SharedData* sharedData, const string& name, HashMap<string, string>& attributesMap)
{
	bool tagFound = false;
	Vector<string>::Iterator helper = mListOfTags.find(name);
	
	if ((mListOfTags.find(name) != mListOfTags.end()) && sharedData->is(SharedDataMotorcycles::typeIdClass()))
	{
		mCurrentElement = name;
		sharedData->as<SharedDataMotorcycles>()->mFoundAttributes.insert(pair<string, Vector<string>>(name, Vector<string>()));
		tagFound = true;
	}

	UNREFERENCED_PARAMETER(attributesMap);
	sharedData->incrementDepth();
	return tagFound;
}

void XMLParseHelperMotorcycle::charDataHandler(XMLParseMaster::SharedData* sharedData, const char* buffer, uint32_t length)
{
	if (sharedData->is(SharedDataMotorcycles::typeIdClass()))
	{
		string temp = string(buffer).substr(0, length);
		sharedData->as<SharedDataMotorcycles>()->mFoundAttributes[mCurrentElement].pushBack(temp);
	}
}

bool XMLParseHelperMotorcycle::endElementHandler(XMLParseMaster::SharedData* sharedData, const string& name)
{
	bool handled = false;
	if ((mListOfTags.find(name) != mListOfTags.end()) && sharedData->is(SharedDataMotorcycles::typeIdClass()))
	{
		handled = true;
	}

	sharedData->decrementDepth();
	return handled;
}

void XMLParseHelperMotorcycle::addTagToHandle(const string& tag)
{
	mListOfTags.pushBack(tag);
}