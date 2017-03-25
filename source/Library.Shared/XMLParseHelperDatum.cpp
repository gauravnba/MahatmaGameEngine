#include "pch.h"

#include "XMLParseHelperDatum.h"
#include "SharedDataTable.h"

using namespace MahatmaGameEngine;
using namespace std;

XMLParseHelperDatum::XMLParseHelperDatum()
{
	mHandledTags.pushBack("Integer");
	mHandledTags.pushBack("Float");
	mHandledTags.pushBack("Vector");
	mHandledTags.pushBack("Matrix");
	mHandledTags.pushBack("String");
}

void XMLParseHelperDatum::initialize()
{
}

XMLParseHelper* XMLParseHelperDatum::clone()
{
	return new XMLParseHelperDatum;
}

bool XMLParseHelperDatum::startElementHandler(XMLParseMaster::SharedData* sharedData, const std::string& name, HashMap<std::string, std::string>& attributesMap)
{
	bool tagFound = false;

	if (sharedData->is(SharedDataTable::typeIdClass()))
	{
		for (uint32_t i = 0; i < mHandledTags.size(); ++i)
		{
			if (mHandledTags[i] == name)
			{
				tagFound = true;
				Scope& tempScope = *(sharedData->as<SharedDataTable>()->mCurrentTable);
				Datum& tempDatum = tempScope[attributesMap["name"]];
				setDatumType(i, tempDatum);
				tempDatum.setFromString(attributesMap["value"], tempDatum.size());
				break;
			}
		}
	}

	return tagFound;
}

bool XMLParseHelperDatum::endElementHandler(XMLParseMaster::SharedData* sharedData, const string& name)
{
	bool handled = false;
	if (sharedData->is(SharedDataTable::typeIdClass()))
	{
		for (uint32_t i = 0; i < mHandledTags.size(); ++i)
		{
			if (mHandledTags[i] == name)
			{
				handled = true;
			}
		}
	}

	return handled;
}

void XMLParseHelperDatum::setDatumType(const uint32_t index, Datum& setTypeOf)
{
	switch (index)
	{
	case 0:
	{
		setTypeOf.setType(DatumType::INTEGER);
		break;
	}
	case 1:
	{
		setTypeOf.setType(DatumType::FLOAT);
		break;
	}
	case 2:
	{
		setTypeOf.setType(DatumType::VECTOR);
		break;
	}
	case 3:
	{
		setTypeOf.setType(DatumType::MATRIX);
		break;
	}
	case 4:
	{
		setTypeOf.setType(DatumType::STRING);
		break;
	}
	}
}