#include "pch.h"
#include "ActionEvent.h"
#include "Event.h"
#include "AttributedMessage.h"
#include "Event.h"
#include "WorldState.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(ActionEvent)

ActionEvent::ActionEvent()
{
	setTheThisAttribute();
	appendExternalAttribute("subType", &mSubType);
	addToPrescribed("subType");
	appendExternalAttribute("delay", &mDelay);
	addToPrescribed("delay");
}

void ActionEvent::update(WorldState& worldState)
{
	worldState.mCurrentAction = this;
	assert(worldState.mEventQueue != nullptr && worldState.mGameTime != nullptr);

	AttributedMessage message(mSubType, worldState);
	shared_ptr<Event<AttributedMessage>> event = make_shared<Event<AttributedMessage>>(message);
	worldState.mEventQueue->enqueue(event, *(worldState.mGameTime), MilliSeconds(mDelay));
}

void ActionEvent::setAttributes(const string& subType, uint32_t delay)
{
	mSubType = subType;
	mDelay = delay;
}

void ActionEvent::setSubType(const string& subType)
{
	mSubType = subType;
}

const string& ActionEvent::getSubType() const
{
	return mSubType;
}

string& ActionEvent::getSubType()
{
	return mSubType;
}

void ActionEvent::setDelay(uint32_t delay)
{
	mDelay = delay;
}

uint32_t ActionEvent::getDelay()
{
	return mDelay;
}