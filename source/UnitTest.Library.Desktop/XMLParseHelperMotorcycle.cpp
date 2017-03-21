#include "pch.h"

#include "XMLParseHelperMotorcycle.h"

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
	mFoundAttributes.clear();
}

XMLParseHelperMotorcycle* XMLParseHelperMotorcycle::clone()
{
	XMLParseHelperMotorcycle* temp = new XMLParseHelperMotorcycle;
	temp->mListOfTags = mListOfTags;
	return temp;
}

bool XMLParseHelperMotorcycle::startElementHandler(const string& name, HashMap<string, string>& attributesMap)
{
	bool tagFound = false;
	Vector<string>::Iterator helper = mListOfTags.find(name);
	
	if (mListOfTags.find(name) != mListOfTags.end())
	{
		mCurrentElement = name;
		mFoundAttributes.insert(pair<string, string>(name, ""));
		tagFound = true;
	}

	UNREFERENCED_PARAMETER(attributesMap);

	return tagFound;
}

void XMLParseHelperMotorcycle::charDataHandler(const char* buffer, uint32_t length)
{
	mFoundAttributes[mCurrentElement] = string(buffer);
	UNREFERENCED_PARAMETER(length);
}

bool XMLParseHelperMotorcycle::endElementHandler(const string& name)
{
	UNREFERENCED_PARAMETER(name);
	return true;
}

void XMLParseHelperMotorcycle::addTagToHandle(const string& tag)
{
	mListOfTags.pushBack(tag);
}