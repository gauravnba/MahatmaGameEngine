#include "pch.h"
#include "AttributedMessage.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(AttributedMessage)

AttributedMessage::AttributedMessage()
{
	populatePrescribed();
}

AttributedMessage::AttributedMessage(const std::string& subType, WorldState& worldState) :
	mSubType(subType), mWorldState(&worldState)
{
	populatePrescribed();
}

AttributedMessage::AttributedMessage(const AttributedMessage& obj) :
	mSubType(obj.mSubType), mWorldState(obj.mWorldState)
{
}

AttributedMessage& AttributedMessage::operator=(const AttributedMessage& obj)
{
	if (this != &obj)
	{
		mSubType = obj.mSubType;
		mWorldState = obj.mWorldState;
	}
	return *this;
}

void AttributedMessage::setSubType(const std::string& subType)
{
	mSubType = subType;
}

string& AttributedMessage::getSubType()
{
	return mSubType;
}

const string& AttributedMessage::getSubType() const
{
	return mSubType;
}

void AttributedMessage::setWorldState(WorldState& worldState)
{
	mWorldState = &worldState;
}

WorldState& AttributedMessage::getWorldState()
{
	return *mWorldState;
}

void AttributedMessage::populatePrescribed()
{
	setTheThisAttribute();
	appendExternalAttribute("subType", &mSubType);
	addToPrescribed("subType");
}