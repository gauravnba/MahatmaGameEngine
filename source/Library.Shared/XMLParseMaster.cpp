#include "pch.h"

#include "XMLParseMaster.h"
#include "XMLParseHelper.h"
#include <fstream>
#include <sstream>

using namespace MahatmaGameEngine;
using namespace std;

#pragma warning (disable : 4075)

#pragma region SharedData

RTTI_DEFINITIONS(XMLParseMaster::SharedData)

void XMLParseMaster::SharedData::initialize()
{
	mXMLParseMaster = nullptr;
	mDepth = 0;
}

void XMLParseMaster::SharedData::setXMLParseMaster(XMLParseMaster* xmlParseMaster)
{
	mXMLParseMaster = xmlParseMaster;
}

XMLParseMaster* XMLParseMaster::SharedData::getXMLParseMaster()
{
	return mXMLParseMaster;
}

XMLParseMaster* const XMLParseMaster::SharedData::getXMLParseMaster() const
{
	return mXMLParseMaster;
}

void XMLParseMaster::SharedData::incrementDepth()
{
	++mDepth;
}

void XMLParseMaster::SharedData::decrementDepth()
{
	--mDepth;
}

std::uint32_t XMLParseMaster::SharedData::depth()
{
	return mDepth;
}

#pragma endregion

#pragma region XMLParseMaster

XMLParseMaster::XMLParseMaster(SharedData* obj) :
	mIsCloned(false), mSharedData(obj), mResponsibleHelperIndex(-1)
{
	mParser = XML_ParserCreate(NULL);
}

void XMLParseMaster::initialize()
{
	XML_ParserReset(mParser, NULL);

	XML_SetUserData(mParser, this);
	XML_SetElementHandler(mParser, startElementHandler, endElementHandler);
	XML_SetCharacterDataHandler(mParser, charDataHandler);

	uint32_t size = mHelpers.size();
	for (uint32_t i = 0; i < size; ++i)
	{
		mHelpers[i]->initialize();
	}

	mSharedData->initialize();
}

XMLParseMaster::~XMLParseMaster()
{
	if (mIsCloned)
	{
		std::uint32_t size = mHelpers.size();
		for (std::uint32_t i = 0; i < size; ++i)
		{
			XMLParseHelper* temp = mHelpers[i];
			delete temp;
		}
		/*while (!mHelpers.isEmpty())
		{
			delete mHelpers[i];
		}*/
		delete mSharedData;
	}

	XML_ParserFree(mParser);
}

XMLParseMaster* XMLParseMaster::clone()
{
	XMLParseMaster* temp = new XMLParseMaster(mSharedData->clone());

	std::uint32_t size = mHelpers.size();
	for (std::uint32_t i = 0; i < size; ++i)
	{
		temp->mHelpers.pushBack(mHelpers[i]->clone());
	}

	temp->mIsCloned = true;

	return temp;
}

void XMLParseMaster::addHelper(XMLParseHelper* parseHelper)
{
	if (!mIsCloned)
	{
		mHelpers.pushBack(parseHelper);
	}
}

void XMLParseMaster::removeHelper(XMLParseHelper* parseHelper)
{
	mHelpers.remove(parseHelper);
}

void XMLParseMaster::parse(const char* data, uint32_t length, bool isLast)
{
	initialize();

	if (XML_Parse(mParser, data, length, isLast) == XML_STATUS_ERROR)
	{
		int code = XML_GetErrorCode(mParser);
		const char* msg = (const char *)XML_ErrorString((XML_Error)code);
		throw runtime_error(msg);
	}
}

void XMLParseMaster::parseFromFile(const string& fileName)
{
	mFileName = fileName;
	
	fstream fileStream;
	fileStream.open(mFileName, fstream::in);

	auto fileContent = static_cast<ostringstream&>(ostringstream{} << fileStream.rdbuf()).str();

	parse(fileContent.c_str(), static_cast<uint32_t>(fileContent.length()), true);
}

string& XMLParseMaster::getFileName()
{
	return mFileName;
}

void XMLParseMaster::setSharedData(SharedData* sharedData)
{
	mSharedData = sharedData;
	mSharedData->setXMLParseMaster(this);
}

XMLParseMaster::SharedData* XMLParseMaster::getSharedData()
{
	return mSharedData;
}

void XMLParseMaster::startElementHandler(void* userData, const char* element, const char** attributes)
{
	int i;
	HashMap<string, string> tempMap;
	XMLParseMaster* castedParseMaster = static_cast<XMLParseMaster*>(userData);

	for (i = 0; attributes[i]; i += 2)
	{
		tempMap.insert(pair<string, string>(attributes[i], attributes[i+1]));
	}

	//chain of responsibility pattern
	uint32_t size = castedParseMaster->mHelpers.size();
	for (uint32_t j = 0; j < size; ++j)
	{
		if (castedParseMaster->mHelpers[j]->startElementHandler(castedParseMaster->getSharedData(), element, tempMap))
		{
			castedParseMaster->mResponsibleHelperIndex = static_cast<int32_t>(j);
			break;
		}
		castedParseMaster->mResponsibleHelperIndex = -1;
	}
}

void XMLParseMaster::endElementHandler(void* userData, const char* element)
{
	XMLParseMaster* castedParseMaster = static_cast<XMLParseMaster*>(userData);

	uint32_t size = castedParseMaster->mHelpers.size();
	for (uint32_t j = 0; j < size; ++j)
	{
		if (castedParseMaster->mHelpers[j]->endElementHandler(castedParseMaster->getSharedData(), element))
		{
			break;
		}
	}

	castedParseMaster->mResponsibleHelperIndex = -1;		//Reset responsible helper that can handle CharacterData.
	castedParseMaster->getSharedData()->decrementDepth();
}

void XMLParseMaster::charDataHandler(void* userData, const char* value, int length)
{
	XMLParseMaster* castedParseMaster = static_cast<XMLParseMaster*>(userData);

	if (castedParseMaster->mResponsibleHelperIndex >= 0 && length != 0)
	{
		castedParseMaster->mHelpers[castedParseMaster->mResponsibleHelperIndex]->charDataHandler(castedParseMaster->getSharedData(), value, length);
	}
}

#pragma endregion