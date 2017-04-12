#include "pch.h"
#include "EventPublisher.h"

using namespace MahatmaGameEngine;
using namespace std;

RTTI_DEFINITIONS(EventPublisher)

EventPublisher::EventPublisher(Vector<EventSubscriber*>& subscriberList) :
	mSubscribers(&subscriberList)
{
}

EventPublisher::EventPublisher(const EventPublisher& obj) :
	mSubscribers(obj.mSubscribers), mTimeEnqueued(obj.mTimeEnqueued), mDelay(obj.mDelay)
{
}

EventPublisher::EventPublisher(EventPublisher&& obj) :
	mTimeEnqueued(move(obj.mTimeEnqueued)), mDelay(move(obj.mDelay)), mSubscribers(obj.mSubscribers)
{
	obj.mSubscribers = nullptr;
}

EventPublisher& EventPublisher::operator=(const EventPublisher& obj)
{
	if (this != &obj)
	{
		mSubscribers = obj.mSubscribers;
		mTimeEnqueued = obj.mTimeEnqueued;
		mDelay = obj.mDelay;
	}
	return *this;
}

EventPublisher& EventPublisher::operator=(EventPublisher&& obj)
{
	if (this != &obj)
	{
		mSubscribers = obj.mSubscribers;
		mTimeEnqueued = move(obj.mTimeEnqueued);
		mDelay = move(obj.mDelay);

		obj.mSubscribers = nullptr;
	}
	return *this;
}

void EventPublisher::setTime(const TimePoint& time, const MilliSeconds& delay)
{
	mTimeEnqueued = time;
	mDelay = delay;
}

TimePoint& EventPublisher::timeEnqueued()
{
	return mTimeEnqueued;
}

bool EventPublisher::isExpired(const TimePoint& currentTime)
{
	if (currentTime >= (mTimeEnqueued + mDelay))
	{
		return true;
	}
	return false;
}

void EventPublisher::deliver()
{
	for (auto subscriber : *mSubscribers)
	{
		subscriber->notify(*this);
	}
}