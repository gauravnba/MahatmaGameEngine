#include "pch.h"

#include "ReactionAttributed.h"
#include "AttributedMessage.h"
#include "Event.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(ReactionAttributed)

ReactionAttributed::ReactionAttributed()
{
	Event<AttributedMessage>::subscribe(*this);
}

ReactionAttributed::~ReactionAttributed()
{
	Event<AttributedMessage>::unsubscribe(*this);
}

void ReactionAttributed::setSubType(const string& subType)
{
	mSubType = subType;
}

string& ReactionAttributed::getSubType()
{
	return mSubType;
}

void ReactionAttributed::notify(const EventPublisher& subscribedTo)
{
	assert(subscribedTo.is(Event<AttributedMessage>::typeIdClass()));
	auto message = static_cast<const Event<AttributedMessage>&>(subscribedTo).message();

	if (message.getSubType() == mSubType)
	{
		copyAuxiliaryAttributes(message);
		ActionList::update(message.getWorldState());
	}
}